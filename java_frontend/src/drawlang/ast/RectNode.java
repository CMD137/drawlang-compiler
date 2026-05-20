/**
 * RECT 命令节点。
 *
 * 对应核心规则中的：
 * RECT(x, y, width, height) COLOR color WIDTH lineWidth rect_fill_part;
 */
package drawlang.ast;

public class RectNode extends CommandNode {
    private final double x;
    private final double y;
    private final double width;
    private final double height;
    private final String color;
    private final double lineWidth;
    private final FillSpec fill;

    public RectNode(double x, double y, double width, double height, String color,
                    double lineWidth, FillSpec fill) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.color = color;
        this.lineWidth = lineWidth;
        this.fill = fill;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

    public String getColor() {
        return color;
    }

    public double getLineWidth() {
        return lineWidth;
    }

    public FillSpec getFill() {
        return fill;
    }

    @Override
    public String getCommandType() {
        return "rect";
    }

    @Override
    public String toString() {
        return "RectNode{x=" + x
            + ", y=" + y
            + ", width=" + width
            + ", height=" + height
            + ", color='" + color + '\''
            + ", lineWidth=" + lineWidth
            + ", fill=" + fill
            + "}";
    }
}
