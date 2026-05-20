/**
 * LR(1) 分析器使用的产生式描述对象。
 *
 * 该结构只保留语法分析真正需要的核心信息：
 * - 产生式编号 id
 * - 左部非终结符 left
 * - 右部长度 rightSize
 * - 人类可读的文法描述 description
 *
 * 其中 rightSize 用于归约时决定状态栈和值栈要弹出多少项。
 */
public class Production {
    private final int id;
    private final NonTerminal left;
    private final int rightSize;
    private final String description;

    public Production(int id, NonTerminal left, int rightSize, String description) {
        this.id = id;
        this.left = left;
        this.rightSize = rightSize;
        this.description = description;
    }

    public int getId() {
        return id;
    }

    public NonTerminal getLeft() {
        return left;
    }

    public int getRightSize() {
        return rightSize;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public String toString() {
        return "(" + id + ") " + description;
    }
}
