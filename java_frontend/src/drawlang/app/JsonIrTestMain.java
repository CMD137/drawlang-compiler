package drawlang.app;

import drawlang.ast.ProgramNode;
import drawlang.lexer.LexicalException;
import drawlang.parser.ParseException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Dedicated JSON IR regression entry for the Java frontend.
 */
public class JsonIrTestMain {
    private static final Path DEFAULT_INPUT = Path.of("..", "tests", "valid", "demo.draw");
    private static final Path DEFAULT_EXPECTED = Path.of("..", "tests", "expected_ir", "demo.json");

    public static void main(String[] args) throws IOException {
        Path inputPath = args.length > 0 ? Path.of(args[0]) : DEFAULT_INPUT;
        Path expectedPath = args.length > 1 ? Path.of(args[1]) : DEFAULT_EXPECTED;

        runJsonIrCase(inputPath, expectedPath);
    }

    private static void runJsonIrCase(Path inputPath, Path expectedPath) throws IOException {
        System.out.println("=== JSON IR Test: " + inputPath + " ===");

        if (!FrontendSupport.validateInputFile(inputPath)) {
            return;
        }

        try {
            String source = FrontendSupport.readSource(inputPath);
            ProgramNode program = FrontendSupport.parseTokens(FrontendSupport.tokenize(source));
            String actualJson = FrontendSupport.emitJsonIr(program);

            System.out.println("[IR Success] " + inputPath);

            if (Files.exists(expectedPath) && Files.isRegularFile(expectedPath)) {
                String expectedJson = Files.readString(expectedPath);
                if (normalizeLineEndings(expectedJson).equals(normalizeLineEndings(actualJson))) {
                    System.out.println("[IR Match] " + expectedPath);
                } else {
                    System.out.println("[IR Mismatch] " + expectedPath);
                }
            } else {
                System.out.println("[IR Warning] Expected IR file not found: " + expectedPath);
            }

            System.out.println(actualJson);
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }

    private static String normalizeLineEndings(String text) {
        String normalized = text.replace("\r\n", "\n").replace('\r', '\n');
        while (normalized.endsWith("\n")) {
            normalized = normalized.substring(0, normalized.length() - 1);
        }
        return normalized;
    }
}
