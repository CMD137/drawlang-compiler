package drawlang.app;

import drawlang.ast.ProgramNode;
import drawlang.lexer.LexicalException;
import drawlang.lexer.Token;
import drawlang.parser.ParseException;
import java.io.IOException;
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

        if (!FrontendSupport.validateInputFile(inputPath)) {
            return;
        }

        try {
            String source = FrontendSupport.readSource(inputPath);
            List<Token> tokens = FrontendSupport.tokenize(source);
            ProgramNode program = FrontendSupport.parseTokens(tokens);
            FrontendSupport.printAstSummary(inputPath, program);
        } catch (LexicalException ex) {
            System.out.println(ex.getMessage());
        } catch (ParseException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
