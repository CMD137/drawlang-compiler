package drawlang.parser;

import java.util.EnumMap;
import java.util.Map;

/**
 * 非终结符枚举。
 *
 * 虽然 {@link GrammarSymbol} 已包含全部非终结符，但单独保留此枚举有两个好处：
 * 1. 与文档中的 `gotoTable : Map<Integer, Map<NonTerminal, Integer>>` 设计保持一致
 * 2. 在代码层明确限制 GOTO 表只能接收非终结符，避免误把终结符放进去
 */
public enum NonTerminal {
    ACCEPT(GrammarSymbol.ACCEPT),
    PROGRAM(GrammarSymbol.PROGRAM),
    STMT_LIST(GrammarSymbol.STMT_LIST),
    STATEMENT(GrammarSymbol.STATEMENT),
    LINE_STMT(GrammarSymbol.LINE_STMT),
    RECT_STMT(GrammarSymbol.RECT_STMT),
    CIRCLE_STMT(GrammarSymbol.CIRCLE_STMT),
    TEXT_STMT(GrammarSymbol.TEXT_STMT),
    RECT_FILL_PART(GrammarSymbol.RECT_FILL_PART),
    CIRCLE_FILL_PART(GrammarSymbol.CIRCLE_FILL_PART),
    NUMBER(GrammarSymbol.NUMBER_NON_TERMINAL),
    STRING(GrammarSymbol.STRING_NON_TERMINAL),
    COLOR_NAME(GrammarSymbol.COLOR_NAME);

    private static final Map<GrammarSymbol, NonTerminal> LOOKUP = buildLookup();

    private final GrammarSymbol symbol;

    NonTerminal(GrammarSymbol symbol) {
        this.symbol = symbol;
    }

    private static Map<GrammarSymbol, NonTerminal> buildLookup() {
        Map<GrammarSymbol, NonTerminal> lookup = new EnumMap<>(GrammarSymbol.class);
        for (NonTerminal nonTerminal : values()) {
            lookup.put(nonTerminal.getSymbol(), nonTerminal);
        }
        return lookup;
    }

    /**
     * 返回该非终结符对应的统一语法符号。
     *
     * @return GrammarSymbol 中的非终结符条目
     */
    public GrammarSymbol getSymbol() {
        return symbol;
    }

    /**
     * 由统一语法符号反查非终结符枚举。
     *
     * @param symbol GrammarSymbol 中的非终结符
     * @return 对应的 NonTerminal
     */
    public static NonTerminal fromSymbol(GrammarSymbol symbol) {
        NonTerminal nonTerminal = LOOKUP.get(symbol);
        if (nonTerminal == null) {
            throw new IllegalArgumentException("Symbol is not a registered non-terminal: " + symbol);
        }
        return nonTerminal;
    }
}
