/**
 * 词法分析异常。
 *
 * 当输入中出现无法识别的字符、非法数字、未闭合字符串等问题时，
 * 由 Lexer 抛出该异常。
 */
package drawlang.lexer;

public class LexicalException extends RuntimeException {
    public LexicalException(String message) {
        super(message);
    }
}
