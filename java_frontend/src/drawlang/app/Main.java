package drawlang.app;

import drawlang.ast.ProgramNode;
import drawlang.lexer.LexicalException;
import drawlang.lexer.Token;
import drawlang.parser.ParseException;
import java.io.IOException;
import java.nio.file.Path;
import java.util.List;

/**
 * Main entry for the current Java frontend.
 */
public class Main {
    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            printUsage();
            return;
        }

        Path inputPath = Path.of(args[0]);

        if (!FrontendSupport.validateInputFile(inputPath)) {
            return;
        }

        try {
            String source = FrontendSupport.readSource(inputPath);
            List<Token> tokens = FrontendSupport.tokenize(source);
            ProgramNode program = FrontendSupport.parseTokens(tokens);
            FrontendSupport.printAstSummary(inputPath, program);
            System.out.println();
            FrontendSupport.printJsonIr(program);
            Path outputPath = FrontendSupport.writeDefaultJsonIr(inputPath, program);
            System.out.println("[IR Output] " + outputPath);
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }

    private static void printUsage() {
        System.out.println("Usage: java -jar java_frontend.jar <input.draw>");
    }
}
