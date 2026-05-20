/**
 * LINE 命令节点。
 *
 * 对应核心规则中的：
 * LINE(x1, y1, x2, y2) COLOR color WIDTH lineWidth;
 */
package drawlang.ast;

public class LineNode extends CommandNode {
    private final double x1;
    private final double y1;
    private final double x2;
    private final double y2;
    private final String color;
    private final double lineWidth;

    public LineNode(double x1, double y1, double x2, double y2, String color, double lineWidth) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.color = color;
        this.lineWidth = lineWidth;
    }

    public double getX1() {
        return x1;
    }

    public double getY1() {
        return y1;
    }

    public double getX2() {
        return x2;
    }

    public double getY2() {
        return y2;
    }

    public String getColor() {
        return color;
    }

    public double getLineWidth() {
        return lineWidth;
    }

    @Override
    public String getCommandType() {
        return "line";
    }

    @Override
    public String toString() {
        return "LineNode{x1=" + x1
            + ", y1=" + y1
            + ", x2=" + x2
            + ", y2=" + y2
            + ", color='" + color + '\''
            + ", lineWidth=" + lineWidth
            + "}";
    }
}
