/**
 * Token 表示词法分析器识别出的一个最小语法单位。
 *
 * 一个 token 由四部分组成：
 * 1. type   : token 类型
 * 2. lexeme : 原始词素内容
 * 3. line   : 词素起始行号
 * 4. column : 词素起始列号
 *
 * 记录行号和列号的目的主要是为了报错时能够精确定位问题位置。
 */
package drawlang.lexer;

public class Token {
    private final TokenType type;
    private final String lexeme;
    private final int line;
    private final int column;

    /**
     * 构造一个 token。
     *
     * @param type token 类型
     * @param lexeme token 的原始词素
     * @param line token 起始行号
     * @param column token 起始列号
     */
    public Token(TokenType type, String lexeme, int line, int column) {
        this.type = type;
        this.lexeme = lexeme;
        this.line = line;
        this.column = column;
    }

    public TokenType getType() {
        return type;
    }

    public String getLexeme() {
        return lexeme;
    }

    public int getLine() {
        return line;
    }

    public int getColumn() {
        return column;
    }

    @Override
    public String toString() {
        // 统一打印格式，方便调试 lexer 输出。
        return String.format("%-10s line=%d col=%d lexeme=%s", type, line, column, lexeme);
    }
}
