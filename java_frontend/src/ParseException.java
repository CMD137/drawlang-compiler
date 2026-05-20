import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 语法分析异常。
 *
 * 该异常用于封装 LR(1) parser 在 ACTION/GOTO 查询失败时
 * 需要反馈给用户的关键信息：
 * - 出错位置
 * - 实际读到的 token 类型
 * - 当前状态下本应接受的 token 类型集合
 */
public class ParseException extends RuntimeException {
    private final int line;
    private final int column;
    private final TokenType actual;
    private final List<TokenType> expected;

    public ParseException(int line, int column, TokenType actual, List<TokenType> expected) {
        super(buildMessage(line, column, actual, expected));
        this.line = line;
        this.column = column;
        this.actual = actual;
        List<TokenType> safeExpected = expected == null ? Collections.emptyList() : expected;
        this.expected = Collections.unmodifiableList(new ArrayList<>(safeExpected));
    }

    private static String buildMessage(int line, int column, TokenType actual, List<TokenType> expected) {
        String expectedText;
        if (expected == null || expected.isEmpty()) {
            expectedText = "<unavailable>";
        } else {
            expectedText = expected.stream()
                .map(Enum::name)
                .collect(Collectors.joining(", "));
        }
        return String.format(
            "[Error][Syntax ] line %d, col %d: unexpected token %s, expected %s",
            line,
            column,
            actual,
            expectedText
        );
    }

    public int getLine() {
        return line;
    }

    public int getColumn() {
        return column;
    }

    public TokenType getActual() {
        return actual;
    }

    public List<TokenType> getExpected() {
        return expected;
    }
}
