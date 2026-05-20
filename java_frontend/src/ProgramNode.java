import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * DrawLang 程序根节点。
 *
 * 根据核心规则说明，AST 采用“程序根节点 + 扁平命令列表”的结构，
 * 不再为每条语句单独保留 statement 包装层。这样更贴合语言本身
 * 的顺序执行特征，也更便于后续直接输出 JSON IR。
 */
public class ProgramNode {
    private final List<CommandNode> commands;

    /**
     * 使用命令列表构造程序节点。
     *
     * 这里会复制输入列表并对外暴露只读视图，避免后续阶段误修改 AST。
     *
     * @param commands 程序中的绘图命令列表，可以为空但不能为 null
     */
    public ProgramNode(List<CommandNode> commands) {
        if (commands == null) {
            throw new IllegalArgumentException("commands must not be null");
        }
        this.commands = Collections.unmodifiableList(new ArrayList<>(commands));
    }

    /**
     * 返回程序中的命令列表。
     *
     * @return 只读命令列表
     */
    public List<CommandNode> getCommands() {
        return commands;
    }

    /**
     * 程序是否为空。
     *
     * 空程序在文法中由 `Program -> EOF` 归约得到，
     * 因而这里保留显式的空程序表示。
     *
     * @return 若没有命令则返回 true
     */
    public boolean isEmpty() {
        return commands.isEmpty();
    }

    /**
     * 返回命令条数。
     *
     * @return 命令数量
     */
    public int size() {
        return commands.size();
    }

    @Override
    public String toString() {
        return "ProgramNode{commands=" + commands + "}";
    }
}
