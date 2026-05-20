package drawlang.app;

import drawlang.ast.CircleNode;
import drawlang.ast.CommandNode;
import drawlang.ast.FillSpec;
import drawlang.ast.LineNode;
import drawlang.ast.ProgramNode;
import drawlang.ast.RectNode;
import drawlang.ast.TextNode;
import java.math.BigDecimal;

/**
 * Emits the shared DrawLang JSON IR from the current Java AST.
 */
public final class JsonEmitter {
    private static final String INDENT = "  ";
    private static final String NEWLINE = "\n";

    private JsonEmitter() {
    }

    public static String emit(ProgramNode program) {
        if (program == null) {
            throw new IllegalArgumentException("program must not be null");
        }

        StringBuilder builder = new StringBuilder();
        builder.append('{').append(NEWLINE);
        builder.append(indent(1)).append("\"commands\": [").append(NEWLINE);

        for (int i = 0; i < program.getCommands().size(); i++) {
            CommandNode command = program.getCommands().get(i);
            appendCommand(builder, command, i < program.getCommands().size() - 1);
        }

        builder.append(indent(1)).append(']').append(NEWLINE);
        builder.append('}');
        return builder.toString();
    }

    private static void appendCommand(StringBuilder builder, CommandNode command, boolean hasNext) {
        builder.append(indent(2)).append('{').append(NEWLINE);

        if (command instanceof LineNode) {
            LineNode line = (LineNode) command;
            appendLine(builder, line);
        } else if (command instanceof RectNode) {
            RectNode rect = (RectNode) command;
            appendRect(builder, rect);
        } else if (command instanceof CircleNode) {
            CircleNode circle = (CircleNode) command;
            appendCircle(builder, circle);
        } else if (command instanceof TextNode) {
            TextNode text = (TextNode) command;
            appendText(builder, text);
        } else {
            throw new IllegalArgumentException("Unsupported command node: " + command.getClass().getName());
        }

        builder.append(indent(2)).append('}');
        if (hasNext) {
            builder.append(',');
        }
        builder.append(NEWLINE);
    }

    private static void appendLine(StringBuilder builder, LineNode line) {
        appendStringField(builder, 3, "type", line.getCommandType(), true);
        appendNumberField(builder, 3, "x1", line.getX1(), true);
        appendNumberField(builder, 3, "y1", line.getY1(), true);
        appendNumberField(builder, 3, "x2", line.getX2(), true);
        appendNumberField(builder, 3, "y2", line.getY2(), true);
        appendStringField(builder, 3, "color", line.getColor(), true);
        appendNumberField(builder, 3, "lineWidth", line.getLineWidth(), false);
    }

    private static void appendRect(StringBuilder builder, RectNode rect) {
        appendStringField(builder, 3, "type", rect.getCommandType(), true);
        appendNumberField(builder, 3, "x", rect.getX(), true);
        appendNumberField(builder, 3, "y", rect.getY(), true);
        appendNumberField(builder, 3, "width", rect.getWidth(), true);
        appendNumberField(builder, 3, "height", rect.getHeight(), true);
        appendStringField(builder, 3, "color", rect.getColor(), true);
        appendNumberField(builder, 3, "lineWidth", rect.getLineWidth(), true);
        appendFillField(builder, 3, rect.getFill(), false);
    }

    private static void appendCircle(StringBuilder builder, CircleNode circle) {
        appendStringField(builder, 3, "type", circle.getCommandType(), true);
        appendNumberField(builder, 3, "cx", circle.getCx(), true);
        appendNumberField(builder, 3, "cy", circle.getCy(), true);
        appendNumberField(builder, 3, "radius", circle.getRadius(), true);
        appendStringField(builder, 3, "color", circle.getColor(), true);
        appendNumberField(builder, 3, "lineWidth", circle.getLineWidth(), true);
        appendFillField(builder, 3, circle.getFill(), false);
    }

    private static void appendText(StringBuilder builder, TextNode text) {
        appendStringField(builder, 3, "type", text.getCommandType(), true);
        appendNumberField(builder, 3, "x", text.getX(), true);
        appendNumberField(builder, 3, "y", text.getY(), true);
        appendStringField(builder, 3, "content", text.getContent(), true);
        appendStringField(builder, 3, "color", text.getColor(), true);
        appendNumberField(builder, 3, "fontSize", text.getFontSize(), false);
    }

    private static void appendFillField(StringBuilder builder, int level, FillSpec fill, boolean hasNext) {
        if (fill == null || !fill.hasFill()) {
            appendNullField(builder, level, "fill", hasNext);
            return;
        }
        appendStringField(builder, level, "fill", fill.getFillColor(), hasNext);
    }

    private static void appendNumberField(StringBuilder builder, int level, String key,
                                          double value, boolean hasNext) {
        appendFieldPrefix(builder, level, key);
        builder.append(formatNumber(value));
        appendFieldSuffix(builder, hasNext);
    }

    private static void appendStringField(StringBuilder builder, int level, String key,
                                          String value, boolean hasNext) {
        appendFieldPrefix(builder, level, key);
        builder.append('"').append(escapeJson(value)).append('"');
        appendFieldSuffix(builder, hasNext);
    }

    private static void appendNullField(StringBuilder builder, int level, String key, boolean hasNext) {
        appendFieldPrefix(builder, level, key);
        builder.append("null");
        appendFieldSuffix(builder, hasNext);
    }

    private static void appendFieldPrefix(StringBuilder builder, int level, String key) {
        builder.append(indent(level)).append('"').append(key).append("\": ");
    }

    private static void appendFieldSuffix(StringBuilder builder, boolean hasNext) {
        if (hasNext) {
            builder.append(',');
        }
        builder.append(NEWLINE);
    }

    private static String indent(int level) {
        return INDENT.repeat(level);
    }

    private static String formatNumber(double value) {
        if (Double.isNaN(value) || Double.isInfinite(value)) {
            throw new IllegalArgumentException("JSON IR does not support non-finite numbers: " + value);
        }

        double normalizedValue = value == 0.0d ? 0.0d : value;
        return BigDecimal.valueOf(normalizedValue).stripTrailingZeros().toPlainString();
    }

    private static String escapeJson(String value) {
        if (value == null) {
            throw new IllegalArgumentException("JSON string field must not be null");
        }

        StringBuilder escaped = new StringBuilder();
        for (int i = 0; i < value.length(); i++) {
            char current = value.charAt(i);
            switch (current) {
                case '"':
                    escaped.append("\\\"");
                    break;
                case '\\':
                    escaped.append("\\\\");
                    break;
                case '\b':
                    escaped.append("\\b");
                    break;
                case '\f':
                    escaped.append("\\f");
                    break;
                case '\n':
                    escaped.append("\\n");
                    break;
                case '\r':
                    escaped.append("\\r");
                    break;
                case '\t':
                    escaped.append("\\t");
                    break;
                default:
                    if (current < 0x20) {
                        escaped.append(String.format("\\u%04x", (int) current));
                    } else {
                        escaped.append(current);
                    }
                    break;
            }
        }
        return escaped.toString();
    }
}
