import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 * 当前 Java 前端的临时测试入口。
 *
 * 现阶段它只负责驱动 Lexer：
 * - 从文件读取源程序
 * - 调用词法分析器生成 token 序列
 * - 将 token 打印到控制台
 *
 * 后续在加入 LR(1) Parser、AST、语义分析和 JSON IR 后，
 * 这个入口会逐步扩展成完整前端入口。
 */
public class Main {
    public static void main(String[] args) throws IOException {
        // 当前阶段为了方便调试，直接固定读取 samples 目录下的测试文件。
        // 等前端主流程稳定后，再恢复为命令行参数输入。
        Path inputPath = Path.of("samples", "test.draw");
        if (!validateInputFile(inputPath)) {
            return;
        }

        // 读取整个源文件，交给 Lexer 统一扫描。
        String source = Files.readString(inputPath);
        Lexer lexer = new Lexer(source);

        try {
            List<Token> tokens = lexer.tokenize();
            // 当前阶段直接打印 token 流，便于检查词法分析结果。
            for (Token token : tokens) {
                System.out.println(token);
            }
        } catch (LexicalException ex) {
            // 词法错误暂时直接输出到控制台。
            System.out.println(ex.getMessage());
        }
    }

    /**
     * 对输入文件做基础校验。
     *
     * 当前校验内容包括：
     * 1. 路径是否存在
     * 2. 是否为普通文件
     * 3. 后缀是否为 .draw
     *
     * 说明：
     * - 这里的后缀校验主要是为了增强使用规范和用户提示
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
