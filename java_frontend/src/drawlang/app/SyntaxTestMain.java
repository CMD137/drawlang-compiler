package drawlang.app;

import drawlang.ast.ProgramNode;
import drawlang.lexer.LexicalException;
import drawlang.parser.ParseException;
import java.io.IOException;
import java.nio.file.Path;

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
        Path.of("..", "tests", "valid", "demo.draw"),
        Path.of("..", "tests", "syntax_errors", "missing_semicolon.draw"),
        Path.of("..", "tests", "syntax_errors", "missing_rparen.draw"),
        Path.of("..", "tests", "syntax_errors", "missing_comma.draw"),
        Path.of("..", "tests", "syntax_errors", "missing_fill_color.draw"),
        Path.of("..", "tests", "syntax_errors", "unexpected_trailing_token.draw"),
        Path.of("..", "tests", "semantic_errors", "invalid_color.draw"),
        Path.of("..", "tests", "semantic_errors", "out_of_bounds_circle.draw")
    };

    public static void main(String[] args) throws IOException {
        for (Path testCase : TEST_CASES) {
            runSyntaxCase(testCase);
            System.out.println();
        }
    }

    private static void runSyntaxCase(Path inputPath) throws IOException {
        System.out.println("=== Syntax Test: " + inputPath + " ===");

        if (!FrontendSupport.validateInputFile(inputPath)) {
            return;
        }

        try {
            String source = FrontendSupport.readSource(inputPath);
            ProgramNode program = FrontendSupport.parseTokens(FrontendSupport.tokenize(source));
            FrontendSupport.printAstSummary(inputPath, program);
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
