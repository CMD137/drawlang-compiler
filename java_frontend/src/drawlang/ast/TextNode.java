/**
 * TEXT 命令节点。
 *
 * 对应核心规则中的：
 * TEXT(x, y, content) COLOR color SIZE fontSize;
 */
package drawlang.ast;

public class TextNode extends CommandNode {
    private final double x;
    private final double y;
    private final String content;
    private final String color;
    private final double fontSize;

    public TextNode(double x, double y, String content, String color, double fontSize) {
        this.x = x;
        this.y = y;
        this.content = content;
        this.color = color;
        this.fontSize = fontSize;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public String getContent() {
        return content;
    }

    public String getColor() {
        return color;
    }

    public double getFontSize() {
        return fontSize;
    }

    @Override
    public String getCommandType() {
        return "text";
    }

    @Override
    public String toString() {
        return "TextNode{x=" + x
            + ", y=" + y
            + ", content='" + content + '\''
            + ", color='" + color + '\''
            + ", fontSize=" + fontSize
            + "}";
    }
}
