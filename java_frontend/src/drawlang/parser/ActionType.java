/**
 * LR(1) ACTION 表中的动作类型。
 */
package drawlang.parser;

public enum ActionType {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
}
