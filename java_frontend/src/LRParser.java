import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * DrawLang 的手写 LR(1) 表驱动语法分析器骨架。
 *
 * 当前类已经完成两部分基础工作：
 * 1. 固定标准 LR(1) 解析主循环外形
 * 2. 固定所有产生式对应的 AST 归约语义
 *
 * 这意味着后续真正补完 parser 时，主要只剩下一项任务：
 * - 把静态 ACTION/GOTO 表填入 {@link LRParsingTable}
 *
 * 在那之前，本类虽然可以编译，但若分析表为空，会明确提示调用方
 * “表尚未准备好”，从而避免把不完整骨架误当成可用 parser。
 */
public class LRParser {
    private final List<Token> tokens;
    private final LRParsingTable table;

    private int cursor;
    private Token lookahead;
    private Deque<Integer> stateStack;
    private Deque<Object> valueStack;

    /**
     * 使用默认 LR 表骨架创建 parser。
     *
     * @param tokens lexer 输出的完整 token 序列
     */
    public LRParser(List<Token> tokens) {
        this(tokens, new LRParsingTable());
    }

    /**
     * 使用指定 LR 表创建 parser。
     *
     * @param tokens lexer 输出的完整 token 序列
     * @param table LR(1) 分析表
     */
    public LRParser(List<Token> tokens, LRParsingTable table) {
        if (tokens == null || tokens.isEmpty()) {
            throw new IllegalArgumentException("tokens must not be null or empty");
        }
        if (table == null) {
            throw new IllegalArgumentException("table must not be null");
        }
        this.tokens = tokens;
        this.table = table;
    }

    /**
     * 按标准 LR(1) 表驱动流程执行语法分析。
     *
     * 当前若表尚未填充 ACTION 项，会直接抛出非法状态异常，
     * 这是为了清晰地区分“分析表未完成”和“源程序语法错误”这两类问题。
     *
     * @return 构造完成的程序根节点
     */
    public ProgramNode parse() {
        if (table.isActionTableEmpty()) {
            throw new IllegalStateException(
                "LR parsing table skeleton is ready, but ACTION entries have not been populated yet."
            );
        }

        initialize();
        while (true) {
            int state = currentState();
            GrammarSymbol lookaheadSymbol = GrammarSymbol.fromTokenType(lookahead.getType());
            ActionEntry action = table.getAction(state, lookaheadSymbol);

            if (action == null || action.getType() == ActionType.ERROR) {
                throw syntaxError(state, lookahead);
            }

            switch (action.getType()) {
                case SHIFT:
                    shift(action.getValue());
                    break;
                case REDUCE:
                    reduce(action.getValue());
                    break;
                case ACCEPT:
                    return accept();
                default:
                    throw new IllegalStateException("Unsupported LR action: " + action.getType());
            }
        }
    }

    /**
     * 返回当前 parser 使用的 LR 表。
     *
     * 便于后续调试、打印或单元测试时直接访问已注册的产生式与表项。
     *
     * @return 当前 LRParsingTable
     */
    public LRParsingTable getTable() {
        return table;
    }

    private void initialize() {
        this.cursor = 0;
        this.lookahead = tokens.get(0);
        this.stateStack = new ArrayDeque<>();
        this.valueStack = new ArrayDeque<>();
        this.stateStack.push(0);
    }

    private int currentState() {
        Integer state = stateStack.peek();
        if (state == null) {
            throw new IllegalStateException("State stack is empty");
        }
        return state;
    }

    /**
     * 执行移进动作。
     *
     * 这里把完整 token 压入 valueStack，而不是只压 lexeme，
     * 这样后续像 `Number -> NUMBER`、`String -> STRING` 这类产生式归约时，
     * 可以直接从 token 上获取：
     * - 原始文本
     * - 行列号
     * - token 类型
     */
    private void shift(int nextState) {
        stateStack.push(nextState);
        valueStack.push(lookahead);
        advanceLookahead();
    }

    /**
     * 执行归约动作。
     *
     * 归约流程固定为：
     * 1. 根据产生式右部长度同时弹出状态和值
     * 2. 调用 applyReduction 构造新的语义值
     * 3. 根据当前栈顶状态与左部非终结符查 GOTO
     * 4. 压入新状态与新语义值
     */
    private void reduce(int productionId) {
        Production production = table.getProduction(productionId);
        if (production == null) {
            throw new IllegalStateException("Unknown production id: " + productionId);
        }

        List<Object> rhsValues = popRightHandSideValues(production.getRightSize());
        popStates(production.getRightSize());

        Object reducedValue = applyReduction(production, rhsValues);
        Integer gotoState = table.getGoto(currentState(), production.getLeft());
        if (gotoState == null) {
            throw new IllegalStateException(
                "Missing GOTO entry for state " + currentState() + " and non-terminal " + production.getLeft()
            );
        }

        stateStack.push(gotoState);
        valueStack.push(reducedValue);
    }

    private ProgramNode accept() {
        Object value = valueStack.peek();
        if (value instanceof ProgramNode) {
            return (ProgramNode) value;
        }

        // 对应 Bison 的 `$accept -> program $end` 时，手写 parser 会先把 EOF 哨兵移进，
        // 因此接受状态下栈顶可能是 EOF token，而真正的 ProgramNode 位于其下一层。
        if (value instanceof Token && ((Token) value).getType() == TokenType.EOF) {
            valueStack.pop();
            Object programValue = valueStack.peek();
            if (programValue instanceof ProgramNode) {
                return (ProgramNode) programValue;
            }
        }

        throw new IllegalStateException("Accept state reached but no ProgramNode was found on the value stack");
    }

    private void advanceLookahead() {
        if (cursor < tokens.size() - 1) {
            cursor++;
        }
        lookahead = tokens.get(cursor);
    }

    private void popStates(int count) {
        for (int i = 0; i < count; i++) {
            if (stateStack.isEmpty()) {
                throw new IllegalStateException("State stack underflow during reduction");
            }
            stateStack.pop();
        }
    }

    /**
     * 以“从左到右”的顺序返回产生式右部的语义值。
     *
     * 由于栈顶元素天然是最右侧符号，这里在弹出时插到列表前端，
     * 从而保证 `rhsValues.get(0)` 永远是产生式右部第一个符号的语义值。
     */
    private List<Object> popRightHandSideValues(int count) {
        List<Object> values = new ArrayList<>(count);
        for (int i = 0; i < count; i++) {
            if (valueStack.isEmpty()) {
                throw new IllegalStateException("Value stack underflow during reduction");
            }
            values.add(0, valueStack.pop());
        }
        return values;
    }

    /**
     * 统一定义每个产生式归约后返回什么语义值。
     *
     * 这部分正是后续 AST 构造的核心接口约定。即便 ACTION/GOTO 表尚未补齐，
     * 这里也应该尽早固定下来，以保证：
     * - 产生式编号
     * - 归约结果类型
     * - AST 字段映射关系
     *
     * 三者始终一致。
     */
    private Object applyReduction(Production production, List<Object> rhsValues) {
        switch (production.getId()) {
            case 0:
                // $accept -> program
                return rhsValues.get(0);
            case 1:
                // program -> stmt_list
                return new ProgramNode(asCommandList(rhsValues.get(0)));
            case 2:
                // stmt_list -> stmt_list statement
                List<CommandNode> appended = new ArrayList<>(asCommandList(rhsValues.get(0)));
                appended.add(asCommandNode(rhsValues.get(1)));
                return appended;
            case 3:
                // stmt_list -> ε
                return new ArrayList<CommandNode>();
            case 4:
            case 5:
            case 6:
            case 7:
                // statement -> line_stmt | rect_stmt | circle_stmt | text_stmt
                return asCommandNode(rhsValues.get(0));
            case 8:
                // line_stmt -> LINE LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number SEMICOLON
                return new LineNode(
                    asDouble(rhsValues.get(2)),
                    asDouble(rhsValues.get(4)),
                    asDouble(rhsValues.get(6)),
                    asDouble(rhsValues.get(8)),
                    asString(rhsValues.get(11)),
                    asDouble(rhsValues.get(13))
                );
            case 9:
                // rect_stmt -> RECT LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number rect_fill_part SEMICOLON
                return new RectNode(
                    asDouble(rhsValues.get(2)),
                    asDouble(rhsValues.get(4)),
                    asDouble(rhsValues.get(6)),
                    asDouble(rhsValues.get(8)),
                    asString(rhsValues.get(11)),
                    asDouble(rhsValues.get(13)),
                    asFillSpec(rhsValues.get(14))
                );
            case 10:
                // rect_fill_part -> FILL color_name
                return FillSpec.fill(asString(rhsValues.get(1)));
            case 11:
                // rect_fill_part -> NOFILL
                return FillSpec.noFill();
            case 12:
                // circle_stmt -> CIRCLE LPAREN number COMMA number COMMA number RPAREN COLOR color_name WIDTH number circle_fill_part SEMICOLON
                return new CircleNode(
                    asDouble(rhsValues.get(2)),
                    asDouble(rhsValues.get(4)),
                    asDouble(rhsValues.get(6)),
                    asString(rhsValues.get(9)),
                    asDouble(rhsValues.get(11)),
                    asFillSpec(rhsValues.get(12))
                );
            case 13:
                // circle_fill_part -> FILL color_name
                return FillSpec.fill(asString(rhsValues.get(1)));
            case 14:
                // circle_fill_part -> NOFILL
                return FillSpec.noFill();
            case 15:
                // text_stmt -> TEXT LPAREN number COMMA number COMMA string RPAREN COLOR color_name SIZE number SEMICOLON
                return new TextNode(
                    asDouble(rhsValues.get(2)),
                    asDouble(rhsValues.get(4)),
                    asString(rhsValues.get(6)),
                    asString(rhsValues.get(9)),
                    asDouble(rhsValues.get(11))
                );
            case 16:
                // number -> NUMBER
                return Double.parseDouble(asToken(rhsValues.get(0)).getLexeme());
            case 17:
                // string -> STRING
                return asToken(rhsValues.get(0)).getLexeme();
            case 18:
                // color_name -> IDENTIFIER
                return asToken(rhsValues.get(0)).getLexeme();
            default:
                throw new IllegalStateException("Reduction semantic action not implemented: " + production);
        }
    }

    private ParseException syntaxError(int state, Token actualToken) {
        return new ParseException(
            actualToken.getLine(),
            actualToken.getColumn(),
            actualToken.getType(),
            table.getExpectedTokenTypes(state)
        );
    }

    @SuppressWarnings("unchecked")
    private List<CommandNode> asCommandList(Object value) {
        if (value instanceof List<?>) {
            return (List<CommandNode>) value;
        }
        throw new IllegalStateException("Expected List<CommandNode>, but got: " + describeValue(value));
    }

    private CommandNode asCommandNode(Object value) {
        if (value instanceof CommandNode) {
            return (CommandNode) value;
        }
        throw new IllegalStateException("Expected CommandNode, but got: " + describeValue(value));
    }

    private FillSpec asFillSpec(Object value) {
        if (value instanceof FillSpec) {
            return (FillSpec) value;
        }
        throw new IllegalStateException("Expected FillSpec, but got: " + describeValue(value));
    }

    private double asDouble(Object value) {
        if (value instanceof Double) {
            return (Double) value;
        }
        throw new IllegalStateException("Expected Double, but got: " + describeValue(value));
    }

    private String asString(Object value) {
        if (value instanceof String) {
            return (String) value;
        }
        throw new IllegalStateException("Expected String, but got: " + describeValue(value));
    }

    private Token asToken(Object value) {
        if (value instanceof Token) {
            return (Token) value;
        }
        throw new IllegalStateException("Expected Token, but got: " + describeValue(value));
    }

    private String describeValue(Object value) {
        if (value == null) {
            return "null";
        }
        return value.getClass().getSimpleName() + "(" + value + ")";
    }
}
