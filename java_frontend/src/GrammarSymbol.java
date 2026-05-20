import java.util.EnumMap;
import java.util.Map;

/**
 * LR(1) 分析表中使用的统一语法符号枚举。
 *
 * 说明：
 * 1. 终结符与非终结符统一放在一个枚举中，方便 ACTION 表直接以符号为键
 * 2. 与 Lexer 输出的 {@link TokenType} 分离，避免把“词法分类”与“语法符号”
 *    混在一起使用
 * 3. 对于终结符，保留与 TokenType 的映射关系，便于由 lookahead 查询 ACTION
 */
public enum GrammarSymbol {
    // 终结符
    LINE(true, "LINE", TokenType.LINE),
    RECT(true, "RECT", TokenType.RECT),
    CIRCLE(true, "CIRCLE", TokenType.CIRCLE),
    TEXT(true, "TEXT", TokenType.TEXT),
    COLOR(true, "COLOR", TokenType.COLOR),
    WIDTH(true, "WIDTH", TokenType.WIDTH),
    FILL(true, "FILL", TokenType.FILL),
    NOFILL(true, "NOFILL", TokenType.NOFILL),
    SIZE(true, "SIZE", TokenType.SIZE),
    NUMBER(true, "NUMBER", TokenType.NUMBER),
    STRING(true, "STRING", TokenType.STRING),
    IDENTIFIER(true, "IDENTIFIER", TokenType.IDENTIFIER),
    LPAREN(true, "LPAREN", TokenType.LPAREN),
    RPAREN(true, "RPAREN", TokenType.RPAREN),
    COMMA(true, "COMMA", TokenType.COMMA),
    SEMICOLON(true, "SEMICOLON", TokenType.SEMICOLON),
    EOF(true, "EOF", TokenType.EOF),

    // 非终结符
    ACCEPT(false, "$accept", null),
    PROGRAM(false, "program", null),
    STMT_LIST(false, "stmt_list", null),
    STATEMENT(false, "statement", null),
    LINE_STMT(false, "line_stmt", null),
    RECT_STMT(false, "rect_stmt", null),
    CIRCLE_STMT(false, "circle_stmt", null),
    TEXT_STMT(false, "text_stmt", null),
    RECT_FILL_PART(false, "rect_fill_part", null),
    CIRCLE_FILL_PART(false, "circle_fill_part", null),
    NUMBER_NON_TERMINAL(false, "number", null),
    STRING_NON_TERMINAL(false, "string", null),
    COLOR_NAME(false, "color_name", null);

    private static final Map<TokenType, GrammarSymbol> TERMINAL_LOOKUP = buildTerminalLookup();

    private final boolean terminal;
    private final String displayName;
    private final TokenType tokenType;

    GrammarSymbol(boolean terminal, String displayName, TokenType tokenType) {
        this.terminal = terminal;
        this.displayName = displayName;
        this.tokenType = tokenType;
    }

    private static Map<TokenType, GrammarSymbol> buildTerminalLookup() {
        Map<TokenType, GrammarSymbol> lookup = new EnumMap<>(TokenType.class);
        for (GrammarSymbol symbol : values()) {
            if (symbol.isTerminal()) {
                lookup.put(symbol.getTokenType(), symbol);
            }
        }
        return lookup;
    }

    /**
     * 判断当前符号是否为终结符。
     *
     * @return true 表示该符号可直接由 lookahead token 映射得到
     */
    public boolean isTerminal() {
        return terminal;
    }

    /**
     * 返回用于打印和报告的文法名称。
     *
     * @return 友好的符号显示名
     */
    public String getDisplayName() {
        return displayName;
    }

    /**
     * 返回与终结符绑定的 TokenType。
     *
     * 对于非终结符该值为 null。
     *
     * @return 对应 TokenType 或 null
     */
    public TokenType getTokenType() {
        return tokenType;
    }

    /**
     * 将词法 token 类型映射为语法分析使用的终结符。
     *
     * @param tokenType 当前 lookahead 的 token 类型
     * @return 对应的 GrammarSymbol 终结符
     */
    public static GrammarSymbol fromTokenType(TokenType tokenType) {
        GrammarSymbol symbol = TERMINAL_LOOKUP.get(tokenType);
        if (symbol == null) {
            throw new IllegalArgumentException("No grammar symbol mapped for token type: " + tokenType);
        }
        return symbol;
    }

    @Override
    public String toString() {
        return displayName;
    }
}
