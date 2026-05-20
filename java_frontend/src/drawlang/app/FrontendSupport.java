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
 * Java 前端调试与测试入口共用的辅助方法。
 *
 * 当前 `Main`、`LexicalTestMain`、`SyntaxTestMain` 都需要重复做这些事：
 * - 校验 `.draw` 输入文件
 * - 读取源文件文本
 * - 执行词法分析
 * - 执行语法分析
 * - 打印 AST 摘要
 *
 * 为了避免同一套逻辑在多个入口类中重复出现，这里统一收敛到一个工具类中。
 */
public final class FrontendSupport {
    private FrontendSupport() {
    }

    /**
     * 对输入文件做基础校验。
     *
     * 当前校验内容包括：
     * 1. 路径是否存在
     * 2. 是否为普通文件
     * 3. 后缀是否为 `.draw`
     *
     * @param inputPath 输入文件路径
     * @return 校验通过返回 true，否则返回 false 并打印提示
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
     * 读取输入文件全文。
     *
     * @param inputPath 输入文件路径
     * @return 源文件文本
     * @throws IOException 读取失败时抛出
     */
    public static String readSource(Path inputPath) throws IOException {
        return Files.readString(inputPath);
    }

    /**
     * 对指定文本执行词法分析。
     *
     * @param source 源程序文本
     * @return 完整 token 序列
     */
    public static List<Token> tokenize(String source) {
        Lexer lexer = new Lexer(source);
        return lexer.tokenize();
    }

    /**
     * 对完整 token 序列执行 LR(1) 语法分析。
     *
     * @param tokens lexer 输出的 token 序列
     * @return 程序 AST 根节点
     */
    public static ProgramNode parseTokens(List<Token> tokens) {
        LRParser parser = new LRParser(tokens);
        return parser.parse();
    }

    /**
     * 打印 AST 摘要，便于调试语法分析结果。
     *
     * @param inputPath 输入文件路径
     * @param program AST 根节点
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
}
