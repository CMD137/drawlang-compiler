import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 * 当前 Java 前端的调试入口。
 *
 * 现阶段入口已经接入：
 * 1. 读取 `.draw` 源文件
 * 2. 调用 Lexer 生成 token 序列
 * 3. 调用手写 LR(1) Parser 构造 AST
 * 4. 输出 AST 摘要，便于核对语法分析结果
 *
 * 后续在加入语义分析和 JSON IR 后，
 * 这里会继续扩展成完整前端入口。
 */
public class Main {
    public static void main(String[] args) throws IOException {
        // 当前阶段仍保留一个默认样例路径，方便直接运行调试。
        // 如果命令行传入了路径参数，则优先使用用户指定文件。
        Path inputPath = args.length > 0
            ? Path.of(args[0])
            : Path.of("samples", "test.draw");

        if (!validateInputFile(inputPath)) {
            return;
        }

        String source = Files.readString(inputPath);
        Lexer lexer = new Lexer(source);

        try {
            List<Token> tokens = lexer.tokenize();
            LRParser parser = new LRParser(tokens);
            ProgramNode program = parser.parse();
            printAstSummary(inputPath, program);
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }

    /**
     * 输出 AST 摘要，便于当前阶段快速确认语法分析是否成功。
     *
     * 这里只做轻量打印，不承担 JSON 导出职责。
     */
    private static void printAstSummary(Path inputPath, ProgramNode program) {
        System.out.println("[Parse Success] " + inputPath);
        System.out.println("Command count: " + program.size());

        int index = 1;
        for (CommandNode command : program.getCommands()) {
            System.out.println(index + ". " + command);
            index++;
        }
    }

    /**
     * 对输入文件做基础校验。
     *
     * 当前校验内容包括：
     * 1. 路径是否存在
     * 2. 是否为普通文件
     * 3. 后缀是否为 `.draw`
     *
     * 说明：
     * - 这里的后缀校验主要用于增强使用规范和用户提示
     * - 真正的语言合法性仍然由后续的词法、语法、语义分析保证
     */
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
