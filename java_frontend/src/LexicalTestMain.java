import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 * 词法分析专项测试入口。
 *
 * 该类不依赖命令行参数，而是在程序内固定列出若干 `.draw` 测试文件，
 * 便于当前课程设计阶段直接运行并观察每一类词法错误是否被正确识别。
 */
public class LexicalTestMain {
    private static final Path[] TEST_CASES = {
        Path.of("..", "..", "tests", "valid", "demo.draw"),
        Path.of("..", "..", "tests", "lexical_errors", "illegal_char.draw"),
        Path.of("..", "..", "tests", "lexical_errors", "unterminated_string.draw"),
        Path.of("..", "..", "tests", "lexical_errors", "invalid_number.draw")
    };

    public static void main(String[] args) throws IOException {
        for (Path testCase : TEST_CASES) {
            runLexicalCase(testCase);
            System.out.println();
        }
    }

    private static void runLexicalCase(Path inputPath) throws IOException {
        System.out.println("=== Lexical Test: " + inputPath + " ===");

        if (!validateInputFile(inputPath)) {
            return;
        }

        String source = Files.readString(inputPath);
        Lexer lexer = new Lexer(source);

        try {
            List<Token> tokens = lexer.tokenize();
            System.out.println("[Lexical Success] Token count: " + tokens.size());
            for (Token token : tokens) {
                System.out.println(token);
            }
        } catch (LexicalException ex) {
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
