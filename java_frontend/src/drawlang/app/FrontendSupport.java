package drawlang.app;

import drawlang.ast.CommandNode;
import drawlang.ast.ProgramNode;
import drawlang.lexer.Lexer;
import drawlang.lexer.Token;
import drawlang.parser.LRParser;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 * Shared helpers for the current Java frontend entry points.
 */
public final class FrontendSupport {
    private FrontendSupport() {
    }

    /**
     * Validates a DrawLang input file before lexing/parsing.
     *
     * @param inputPath input file path
     * @return true when the file exists, is a regular file, and ends with .draw
     */
    public static boolean validateInputFile(Path inputPath) {
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

    /**
     * Reads the full DrawLang source file.
     *
     * @param inputPath input file path
     * @return source text
     * @throws IOException if the file cannot be read
     */
    public static String readSource(Path inputPath) throws IOException {
        return Files.readString(inputPath);
    }

    /**
     * Tokenizes the given source text.
     *
     * @param source source text
     * @return full token stream, including the EOF token produced by the lexer
     */
    public static List<Token> tokenize(String source) {
        Lexer lexer = new Lexer(source);
        return lexer.tokenize();
    }

    /**
     * Parses the full token stream with the hand-written LR(1) parser.
     *
     * @param tokens token stream
     * @return AST root node
     */
    public static ProgramNode parseTokens(List<Token> tokens) {
        LRParser parser = new LRParser(tokens);
        return parser.parse();
    }

    /**
     * Emits the shared JSON IR from the parsed AST.
     *
     * @param program AST root node
     * @return pretty printed JSON IR
     */
    public static String emitJsonIr(ProgramNode program) {
        return JsonEmitter.emit(program);
    }

    /**
     * Prints a compact AST summary for parser debugging.
     *
     * @param inputPath input file path
     * @param program AST root node
     */
    public static void printAstSummary(Path inputPath, ProgramNode program) {
        System.out.println("[Parse Success] " + inputPath);
        System.out.println("Command count: " + program.size());

        int index = 1;
        for (CommandNode command : program.getCommands()) {
            System.out.println(index + ". " + command);
            index++;
        }
    }

    /**
     * Prints the JSON IR emitted from the AST.
     *
     * @param program AST root node
     */
    public static void printJsonIr(ProgramNode program) {
        System.out.println("[JSON IR]");
        System.out.println(emitJsonIr(program));
    }
}
