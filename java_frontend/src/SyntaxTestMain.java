import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 * 语法分析专项测试入口。
 *
 * 该类在程序内部固定列出若干 `.draw` 文件：
 * - 一个合法样例
 * - 多个专门的语法错误样例
 *
 * 这样可以直接验证 hand-written LR(1) parser 的成功路径和失败路径。
 */
public class SyntaxTestMain {
    private static final Path[] TEST_CASES = {
        Path.of("..", "..", "tests", "valid", "demo.draw"),
        Path.of("..", "..", "tests", "syntax_errors", "missing_semicolon.draw"),
        Path.of("..", "..", "tests", "syntax_errors", "missing_rparen.draw"),
        Path.of("..", "..", "tests", "syntax_errors", "missing_comma.draw"),
        Path.of("..", "..", "tests", "syntax_errors", "missing_fill_color.draw"),
        Path.of("..", "..", "tests", "syntax_errors", "unexpected_trailing_token.draw"),
        Path.of("..", "..", "tests", "semantic_errors", "invalid_color.draw"),
        Path.of("..", "..", "tests", "semantic_errors", "out_of_bounds_circle.draw")
    };

    public static void main(String[] args) throws IOException {
        for (Path testCase : TEST_CASES) {
            runSyntaxCase(testCase);
            System.out.println();
        }
    }

    private static void runSyntaxCase(Path inputPath) throws IOException {
        System.out.println("=== Syntax Test: " + inputPath + " ===");

        if (!validateInputFile(inputPath)) {
            return;
        }

        String source = Files.readString(inputPath);
        Lexer lexer = new Lexer(source);

        try {
            List<Token> tokens = lexer.tokenize();
            LRParser parser = new LRParser(tokens);
            ProgramNode program = parser.parse();
            System.out.println("[Parse Success] Command count: " + program.size());

            int index = 1;
            for (CommandNode command : program.getCommands()) {
                System.out.println(index + ". " + command);
                index++;
            }
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }

    private static boolean validateInputFile(Path inputPath) {
        if (!Files.exists(inputPath)) {
            System.out.println("[Input Error] File not found: " + inputPath);
            return false;
        }

        if (!Files.isRegularFile(inputPath)) {
            System.out.println("[Input Error] Not a regular file: " + inputPath);
            return false;
        }

        String fileName = inputPath.getFileName().toString();
        if (!fileName.toLowerCase().endsWith(".draw")) {
            System.out.println("[Input Error] Input file must use the .draw extension: " + inputPath);
            return false;
        }

        return true;
    }
}
