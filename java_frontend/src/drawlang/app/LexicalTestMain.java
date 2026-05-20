package drawlang.app;

import drawlang.lexer.LexicalException;
import drawlang.lexer.Token;
import java.io.IOException;
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
        Path.of("..", "tests", "valid", "demo.draw"),
        Path.of("..", "tests", "lexical_errors", "illegal_char.draw"),
        Path.of("..", "tests", "lexical_errors", "unterminated_string.draw"),
        Path.of("..", "tests", "lexical_errors", "invalid_number.draw")
    };

    public static void main(String[] args) throws IOException {
        for (Path testCase : TEST_CASES) {
            runLexicalCase(testCase);
            System.out.println();
        }
    }

    private static void runLexicalCase(Path inputPath) throws IOException {
        System.out.println("=== Lexical Test: " + inputPath + " ===");

        if (!FrontendSupport.validateInputFile(inputPath)) {
            return;
        }

        try {
            String source = FrontendSupport.readSource(inputPath);
            List<Token> tokens = FrontendSupport.tokenize(source);
            System.out.println("[Lexical Success] Token count: " + tokens.size());
            for (Token token : tokens) {
                System.out.println(token);
            }
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
