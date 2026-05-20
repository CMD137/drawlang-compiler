/**
 * 填充说明节点。
 *
 * 核心规则中，RECT 与 CIRCLE 的填充部分都只有两种形式：
 * - `FILL color`
 * - `NOFILL`
 *
 * 为了让语法分析阶段直接把这两种形式统一为一个结构，
 * 这里使用 hasFill + fillColor 的二元表示。
 */
package drawlang.ast;

public class FillSpec {
    private final boolean hasFill;
    private final String fillColor;

    /**
     * 构造填充说明。
     *
     * 约定：
     * - 当 hasFill = false 时，fillColor 应为 null
     * - 当 hasFill = true 时，fillColor 应为原始颜色名字符串
     *
     * @param hasFill 是否启用填充
     * @param fillColor 填充颜色名；若不填充则应为 null
     */
    public FillSpec(boolean hasFill, String fillColor) {
        if (!hasFill && fillColor != null) {
            throw new IllegalArgumentException("fillColor must be null when hasFill is false");
        }
        if (hasFill && (fillColor == null || fillColor.isBlank())) {
            throw new IllegalArgumentException("fillColor must not be blank when hasFill is true");
        }
        this.hasFill = hasFill;
        this.fillColor = fillColor;
    }

    /**
     * 构造 NOFILL 对应的填充说明。
     *
     * @return 无填充说明
     */
    public static FillSpec noFill() {
        return new FillSpec(false, null);
    }

    /**
     * 构造 FILL color 对应的填充说明。
     *
     * @param color 原始颜色名
     * @return 带颜色的填充说明
     */
    public static FillSpec fill(String color) {
        return new FillSpec(true, color);
    }

    /**
     * 是否存在填充。
     *
     * @return true 表示来自 `FILL color`
     */
    public boolean hasFill() {
        return hasFill;
    }

    /**
     * 返回填充颜色名。
     *
     * 当前阶段保留词法层读到的原始标识符，
     * 是否属于允许颜色集合由语义分析阶段判断。
     *
     * @return 填充颜色名；若无填充则返回 null
     */
    public String getFillColor() {
        return fillColor;
    }

    @Override
    public String toString() {
        return "FillSpec{hasFill=" + hasFill + ", fillColor='" + fillColor + "'}";
    }
}
