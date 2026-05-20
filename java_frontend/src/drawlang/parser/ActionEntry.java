/**
 * LR(1) ACTION 表项。
 *
 * 约定：
 * - SHIFT  时，value 表示目标状态号
 * - REDUCE 时，value 表示产生式编号
 * - ACCEPT 时，value 固定可取 0
 * - ERROR  时，value 固定可取 -1
 */
package drawlang.parser;

public class ActionEntry {
    private final ActionType type;
    private final int value;

    public ActionEntry(ActionType type, int value) {
        this.type = type;
        this.value = value;
    }

    public static ActionEntry shift(int targetState) {
        return new ActionEntry(ActionType.SHIFT, targetState);
    }

    public static ActionEntry reduce(int productionId) {
        return new ActionEntry(ActionType.REDUCE, productionId);
    }

    public static ActionEntry accept() {
        return new ActionEntry(ActionType.ACCEPT, 0);
    }

    public static ActionEntry error() {
        return new ActionEntry(ActionType.ERROR, -1);
    }

    public ActionType getType() {
        return type;
    }

    public int getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "ActionEntry{type=" + type + ", value=" + value + "}";
    }
}
