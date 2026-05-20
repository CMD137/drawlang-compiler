/**
 * CIRCLE 命令节点。
 *
 * 对应核心规则中的：
 * CIRCLE(cx, cy, radius) COLOR color WIDTH lineWidth circle_fill_part;
 */
public class CircleNode extends CommandNode {
    private final double cx;
    private final double cy;
    private final double radius;
    private final String color;
    private final double lineWidth;
    private final FillSpec fill;

    public CircleNode(double cx, double cy, double radius, String color,
                      double lineWidth, FillSpec fill) {
        this.cx = cx;
        this.cy = cy;
        this.radius = radius;
        this.color = color;
        this.lineWidth = lineWidth;
        this.fill = fill;
    }

    public double getCx() {
        return cx;
    }

    public double getCy() {
        return cy;
    }

    public double getRadius() {
        return radius;
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
        return "circle";
    }

    @Override
    public String toString() {
        return "CircleNode{cx=" + cx
            + ", cy=" + cy
            + ", radius=" + radius
            + ", color='" + color + '\''
            + ", lineWidth=" + lineWidth
            + ", fill=" + fill
            + "}";
    }
}
