import java.util.ArrayList;
import java.util.Collections;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 手写 LR(1) 表驱动分析器的静态表容器。
 *
 * 当前阶段的目标不是立即补完全部 ACTION/GOTO 数据，而是先把：
 * 1. 产生式编号体系
 * 2. ACTION/GOTO 的数据结构
 * 3. 后续静态写表时需要的接口
 *
 * 统一固定下来。这样后面补完整 LR(1) 分析表时，只需往本类中
 * 填充状态迁移数据，不需要再改 Parser 外形。
 */
public class LRParsingTable {
    private final Map<Integer, Map<GrammarSymbol, ActionEntry>> actionTable;
    private final Map<Integer, Map<NonTerminal, Integer>> gotoTable;
    private final Map<Integer, Production> productions;

    /**
     * 创建一个仅包含产生式定义的空 LR(1) 表骨架。
     *
     * ACTION/GOTO 仍需在后续根据项目集族静态补齐。
     */
    public LRParsingTable() {
        this.actionTable = new HashMap<>();
        this.gotoTable = new HashMap<>();
        this.productions = new HashMap<>();
        registerDefaultProductions();
        GeneratedParsingTableData.populate(this);
    }

    /**
     * 向 ACTION 表注册一个表项。
     *
     * @param state 状态号
     * @param symbol 终结符
     * @param entry 表项
     * @return 当前表对象，便于链式填表
     */
    public LRParsingTable putAction(int state, GrammarSymbol symbol, ActionEntry entry) {
        if (symbol == null || !symbol.isTerminal()) {
            throw new IllegalArgumentException("ACTION table key must be a terminal symbol");
        }
        actionTable.computeIfAbsent(state, ignored -> new EnumMap<>(GrammarSymbol.class))
            .put(symbol, entry);
        return this;
    }

    /**
     * 向 GOTO 表注册一个表项。
     *
     * @param state 当前状态
     * @param nonTerminal 归约后左部非终结符
     * @param nextState 目标状态
     * @return 当前表对象，便于链式填表
     */
    public LRParsingTable putGoto(int state, NonTerminal nonTerminal, int nextState) {
        if (nonTerminal == null) {
            throw new IllegalArgumentException("nonTerminal must not be null");
        }
        gotoTable.computeIfAbsent(state, ignored -> new EnumMap<>(NonTerminal.class))
            .put(nonTerminal, nextState);
        return this;
    }

    /**
     * 注册产生式。
     *
     * @param production 产生式对象
     * @return 当前表对象
     */
    public LRParsingTable putProduction(Production production) {
        productions.put(production.getId(), production);
        return this;
    }

    /**
     * 查询 ACTION 表项。
     *
     * @param state 状态号
     * @param symbol lookahead 对应的终结符
     * @return 表项；若不存在则返回 null
     */
    public ActionEntry getAction(int state, GrammarSymbol symbol) {
        Map<GrammarSymbol, ActionEntry> row = actionTable.get(state);
        if (row == null) {
            return null;
        }
        return row.get(symbol);
    }

    /**
     * 查询 GOTO 表项。
     *
     * @param state 当前状态
     * @param nonTerminal 左部非终结符
     * @return 目标状态；若不存在则返回 null
     */
    public Integer getGoto(int state, NonTerminal nonTerminal) {
        Map<NonTerminal, Integer> row = gotoTable.get(state);
        if (row == null) {
            return null;
        }
        return row.get(nonTerminal);
    }

    /**
     * 根据产生式编号查询产生式。
     *
     * @param productionId 产生式编号
     * @return 产生式对象；若不存在则返回 null
     */
    public Production getProduction(int productionId) {
        return productions.get(productionId);
    }

    /**
     * 返回某个状态下可能接受的 token 类型列表。
     *
     * 该方法主要服务于语法报错提示：当 ACTION 表查不到 lookahead 时，
     * 可以把当前状态已登记的终结符反推回 TokenType 列表，生成 expected 集合。
     *
     * @param state 当前状态
     * @return 预期 token 类型列表，若没有则返回空列表
     */
    public List<TokenType> getExpectedTokenTypes(int state) {
        Map<GrammarSymbol, ActionEntry> row = actionTable.get(state);
        if (row == null || row.isEmpty()) {
            return Collections.emptyList();
        }

        List<TokenType> result = new ArrayList<>();
        for (Map.Entry<GrammarSymbol, ActionEntry> entry : row.entrySet()) {
            GrammarSymbol symbol = entry.getKey();
            ActionEntry action = entry.getValue();
            if (symbol.isTerminal()
                && symbol.getTokenType() != null
                && action != null
                && action.getType() != ActionType.ERROR) {
                result.add(symbol.getTokenType());
            }
        }
        return result;
    }

    /**
     * 当前表是否还没有任何 ACTION 项。
     *
     * 用于提醒调用方：如果只创建了骨架但还未填表，
     * 那么 parser 还不能真正工作。
     *
     * @return ACTION 表是否为空
     */
    public boolean isActionTableEmpty() {
        return actionTable.isEmpty();
    }

    public Map<Integer, Map<GrammarSymbol, ActionEntry>> getActionTable() {
        return Collections.unmodifiableMap(actionTable);
    }

    public Map<Integer, Map<NonTerminal, Integer>> getGotoTable() {
        return Collections.unmodifiableMap(gotoTable);
    }

    public Map<Integer, Production> getProductions() {
        return Collections.unmodifiableMap(productions);
    }

    /**
     * 注册与核心规则说明一致的默认产生式编号。
     *
     * 这些产生式是整个手写 LR(1) 分析器后续工作的“固定坐标系”。
     * 之后补全 ACTION/GOTO 表、写归约语义、写实验报告时，
     * 都应继续沿用这里的编号与描述。
     */
    private void registerDefaultProductions() {
        putProduction(new Production(0, NonTerminal.ACCEPT, 1, "$accept -> program"));
        putProduction(new Production(1, NonTerminal.PROGRAM, 1, "program -> stmt_list"));
        putProduction(new Production(2, NonTerminal.STMT_LIST, 2, "stmt_list -> stmt_list statement"));
        putProduction(new Production(3, NonTerminal.STMT_LIST, 0, "stmt_list -> ε"));
        putProduction(new Production(4, NonTerminal.STATEMENT, 1, "statement -> line_stmt"));
        putProduction(new Production(5, NonTerminal.STATEMENT, 1, "statement -> rect_stmt"));
        putProduction(new Production(6, NonTerminal.STATEMENT, 1, "statement -> circle_stmt"));
        putProduction(new Production(7, NonTerminal.STATEMENT, 1, "statement -> text_stmt"));
        putProduction(new Production(8, NonTerminal.LINE_STMT, 15,
            "line_stmt -> LINE LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number SEMICOLON"));
        putProduction(new Production(9, NonTerminal.RECT_STMT, 16,
            "rect_stmt -> RECT LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number rect_fill_part SEMICOLON"));
        putProduction(new Production(10, NonTerminal.RECT_FILL_PART, 2, "rect_fill_part -> FILL color_name"));
        putProduction(new Production(11, NonTerminal.RECT_FILL_PART, 1, "rect_fill_part -> NOFILL"));
        putProduction(new Production(12, NonTerminal.CIRCLE_STMT, 14,
            "circle_stmt -> CIRCLE LPAREN number COMMA number COMMA number RPAREN COLOR color_name WIDTH number circle_fill_part SEMICOLON"));
        putProduction(new Production(13, NonTerminal.CIRCLE_FILL_PART, 2, "circle_fill_part -> FILL color_name"));
        putProduction(new Production(14, NonTerminal.CIRCLE_FILL_PART, 1, "circle_fill_part -> NOFILL"));
        putProduction(new Production(15, NonTerminal.TEXT_STMT, 13,
            "text_stmt -> TEXT LPAREN number COMMA number COMMA string RPAREN COLOR color_name SIZE number SEMICOLON"));
        putProduction(new Production(16, NonTerminal.NUMBER, 1, "number -> NUMBER"));
        putProduction(new Production(17, NonTerminal.STRING, 1, "string -> STRING"));
        putProduction(new Production(18, NonTerminal.COLOR_NAME, 1, "color_name -> IDENTIFIER"));
    }
}
