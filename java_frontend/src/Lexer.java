import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * DrawLang 的手工词法分析器。
 *
 * 主要职责：
 * 1. 扫描源程序字符流
 * 2. 识别关键字、标识符、数字、字符串和界符
 * 3. 跳过空白字符与单行注释
 * 4. 维护 token 的行号与列号
 * 5. 发现词法错误时给出清晰错误信息
 *
 * 当前 lexer 的实现方式是典型的“单字符前瞻 + 分类扫描”：
 * - 先看当前字符属于哪一类
 * - 再调用对应的扫描函数把完整 token 读出来
 */
public class Lexer {
    /**
     * 关键字表。
     *
     * 由于语言大小写不敏感，因此扫描标识符后会先转为大写，
     * 再在该表中查找是否属于关键字。
     */
    private static final Map<String, TokenType> KEYWORDS = buildKeywords();
    /**
     * 初始化关键字表。
     *
     * 所有关键字统一存成大写形式，便于与 upper-case 后的词素比较。
     */
    private static Map<String, TokenType> buildKeywords() {
        Map<String, TokenType> keywords = new HashMap<>();
        keywords.put("LINE", TokenType.LINE);
        keywords.put("RECT", TokenType.RECT);
        keywords.put("CIRCLE", TokenType.CIRCLE);
        keywords.put("TEXT", TokenType.TEXT);
        keywords.put("COLOR", TokenType.COLOR);
        keywords.put("WIDTH", TokenType.WIDTH);
        keywords.put("FILL", TokenType.FILL);
        keywords.put("NOFILL", TokenType.NOFILL);
        keywords.put("SIZE", TokenType.SIZE);
        return keywords;
    }

    // 完整源代码文本
    private final String source;
    // 源代码总长度，避免反复调用 source.length()
    private final int length;

    // 当前扫描指针，指向尚未处理的字符
    private int index;

    // 当前指针对应的行号和列号，用于报错定位
    private int line;
    private int column;

    public Lexer(String source) {
        this.source = source == null ? "" : source;
        this.length = this.source.length();
        this.index = 0;
        this.line = 1;
        this.column = 1;
    }

    /**
     * 将整个输入扫描成 token 列表，直到遇到 EOF。
     *
     * @return 完整 token 序列
     */
    public List<Token> tokenize() {
        List<Token> tokens = new ArrayList<>();
        while (true) {
            Token token = nextToken();
            tokens.add(token);
            if (token.getType() == TokenType.EOF) {
                return tokens;
            }
        }
    }

    /**
     * 扫描并返回下一个 token。
     *
     * 实现步骤：
     * 1. 跳过空白和注释
     * 2. 若到达输入末尾，返回 EOF
     * 3. 根据当前字符类别决定进入哪种扫描逻辑
     *
     * @return 下一个 token
     */
    public Token nextToken() {
        //1.跳过所有无意义字符
        skipWhitespaceAndComments();

        //2.文末结束人工构造一个 EOF token
        if (isAtEnd()) {
            return new Token(TokenType.EOF, "<EOF>", line, column);
        }

        char current = peek();
        int startLine = line;
        int startColumn = column;

        //3.根据当前字符类别决定进入哪种扫描逻辑
        switch (current) {
            //单字符界符，直接advance()，然后返回对应的TOKEN
            case '(':
                advance();
                return new Token(TokenType.LPAREN, "(", startLine, startColumn);
            case ')':
                advance();
                return new Token(TokenType.RPAREN, ")", startLine, startColumn);
            case ',':
                advance();
                return new Token(TokenType.COMMA, ",", startLine, startColumn);
            case ';':
                advance();
                return new Token(TokenType.SEMICOLON, ";", startLine, startColumn);
            //"开头扫描字符串
            case '"':
                return scanString(startLine, startColumn);
            default:
                //数字开头读数字
                if (isNumberStart(current)) {
                    return scanNumber(startLine, startColumn);
                }
                //符合标识符首字符规则，识别关键字
                if (isIdentifierStart(current)) {
                    return scanIdentifierOrKeyword(startLine, startColumn);
                }
                throw error(startLine, startColumn, "illegal character '" + current + "'");
        }
    }

    /**
     * 扫描字符串常量。
     *
     * 输入格式要求：
     * - 以双引号开头
     * - 以双引号结尾
     * - 当前版本不支持转义字符
     * - 字符串内部不允许直接跨行
     *
     * 返回的 lexeme 不包含首尾双引号，只保留字符串内容本身。
     */
    private Token scanString(int startLine, int startColumn) {
        // 先吃掉开头的双引号
        advance();
        StringBuilder builder = new StringBuilder();
        while (!isAtEnd() && peek() != '"') {
            char current = peek();
            if (current == '\n' || current == '\r') {
                throw error(startLine, startColumn, "not found right \"");
            }
            builder.append(advance());
        }
        if (isAtEnd()) {
            throw error(startLine, startColumn, "not found right \"");
        }
        advance();
        return new Token(TokenType.STRING, builder.toString(), startLine, startColumn);
    }

    /**
     * 扫描数字常量。
     *
     * 当前支持：
     * - 整数：123
     * - 小数：3.14
     * - 带符号数字：-20, +8.5
     *
     * 注意：
     * 这里的“允许负号”是词法层定义。
     * 真正能否用于坐标或尺寸，要在语义分析阶段再判断是否合法。
     */
    private Token scanNumber(int startLine, int startColumn) {
        StringBuilder builder = new StringBuilder();

        // 若存在显式正负号，先读入。
        if ((peek() == '+' || peek() == '-') && hasNext()) {
            builder.append(advance());
        }

        boolean hasDigit = false;
        while (!isAtEnd() && Character.isDigit(peek())) {
            hasDigit = true;
            builder.append(advance());
        }

        // 若出现小数点，则继续扫描小数部分。
        if (!isAtEnd() && peek() == '.') {
            builder.append(advance());
            while (!isAtEnd() && Character.isDigit(peek())) {
                hasDigit = true;
                builder.append(advance());
            }
        }

        // 例如只有 "+" 或 "-" 或 "." 这种情况不应被接受为合法数字。
        if (!hasDigit) {
            throw error(startLine, startColumn, "invalid number ");
        }

        return new Token(TokenType.NUMBER, builder.toString(), startLine, startColumn);
    }

    /**
     * 扫描标识符或关键字。
     *
     * 处理流程：
     * 1. 读出完整的标识符串
     * 2. 转成大写
     * 3. 若命中关键字表，则返回关键字 token
     * 4. 否则返回 IDENTIFIER
     *
     * 这样可以同时满足：
     * - 语言关键字大小写不敏感
     * - 普通标识符仍保留原始写法
     */
    private Token scanIdentifierOrKeyword(int startLine, int startColumn) {
        StringBuilder builder = new StringBuilder();
        while (!isAtEnd() && isIdentifierPart(peek())) {
            builder.append(advance());
        }

        String lexeme = builder.toString();
        String upper = lexeme.toUpperCase();
        TokenType keyword = KEYWORDS.get(upper);
        if (keyword != null) {
            return new Token(keyword, upper, startLine, startColumn);
        }

        return new Token(TokenType.IDENTIFIER, lexeme, startLine, startColumn);
    }

    /**
     * 跳过所有无意义字符，包括：
     * - 空格
     * - 制表符
     * - 回车
     * - 换行
     * - 以 // 开头的单行注释
     *
     * 这里采用循环处理，是因为跳过一段空白后，后面还可能紧跟着注释；
     * 同理，跳过注释后，后面也可能继续有空白。
     */
    private void skipWhitespaceAndComments() {
        while (!isAtEnd()) {
            char current = peek();
            if (current == ' ' || current == '\t' || current == '\r' || current == '\n') {
                advance();
                continue;
            }
            //处理注释，跳过从 // 到本行结束的全部内容。
            if (current == '/' && peekNext() == '/') {
                while (!isAtEnd() && peek() != '\n') {
                    advance();
                }
                continue;
            }
            return;
        }
    }

    /**
     * 判断当前字符是否可能是数字 token 的起始字符。
     *
     * 合法起始情况包括：
     * - 数字
     * - 带符号数字的 + 或 -
     */
    private boolean isNumberStart(char current) {
        if (Character.isDigit(current)) {
            return true;
        }
        if ((current == '+' || current == '-') && hasNext()) {
            char next = peekNext();
            return Character.isDigit(next) || next == '.';
        }
        return false;
    }

    /**
     * 标识符首字符规则：字母或下划线。
     */
    private boolean isIdentifierStart(char current) {
        return Character.isLetter(current) || current == '_';
    }

    /**
     * 标识符后续字符规则：字母、数字或下划线。
     */
    private boolean isIdentifierPart(char current) {
        return Character.isLetterOrDigit(current) || current == '_';
    }

    private boolean isAtEnd() {
        return index >= length;
    }

    private boolean hasNext() {
        return index + 1 < length;
    }

    private char peek() {
        return source.charAt(index);
    }

    private char peekNext() {
        if (!hasNext()) {
            return '\0';
        }
        return source.charAt(index + 1);
    }

    /**
     * 向前消费一个字符，并同步维护行列号。
     *
     * 规则：
     * - 普通字符：列号加 1
     * - 换行符：行号加 1，列号重置为 1
     */
    private char advance() {
        char current = source.charAt(index++);
        if (current == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        return current;
    }

    /**
     * 构造统一格式的词法错误。
     */
    private LexicalException error(int line, int column, String message) {
        return new LexicalException(
            String.format("[Error][Lexical] line %d, col %d: %s", line, column, message)
        );
    }

}
