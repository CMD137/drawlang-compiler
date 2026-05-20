/**
 * DrawLang AST 中所有绘图命令节点的抽象父类。
 *
 * 当前语言的语句层级非常扁平，每条合法语句都会在语法分析后
 * 归约为一个具体的命令节点：
 * - {@link LineNode}
 * - {@link RectNode}
 * - {@link CircleNode}
 * - {@link TextNode}
 *
 * 之所以保留一个统一的父类，是为了让：
 * 1. {@link ProgramNode} 能够持有统一的命令列表
 * 2. 后续语义检查器可以按统一入口遍历 AST
 * 3. JSON IR 生成器可以根据命令类型进行分派
 */
package drawlang.ast;

public abstract class CommandNode {
    /**
     * 返回命令种类名称。
     *
     * 建议返回与 JSON IR 中 type 字段一致的英文小写，
     * 便于后续前后端共享同一套语义命名。
     *
     * @return 命令类型名，例如 line / rect / circle / text
     */
    public abstract String getCommandType();
}
