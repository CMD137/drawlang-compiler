/**
 * 词法分析阶段输出的 token 类型枚举。
 *
 * 当前语言只支持 4 类绘图命令：
 * LINE / RECT / CIRCLE / TEXT
 *
 * 其余关键字用于描述图形属性，如颜色、线宽、填充、字号等。
 * NUMBER、STRING、IDENTIFIER 是带具体词素内容的通用 token。
 */
package drawlang.lexer;

public enum TokenType {
    // 图形命令关键字
    LINE,
    RECT,
    CIRCLE,
    TEXT,

    // 属性关键字
    COLOR,
    WIDTH,
    FILL,
    NOFILL,
    SIZE,

    // 通用词法单元
    NUMBER,
    STRING,
    IDENTIFIER,

    // 界符
    LPAREN,
    RPAREN,
    COMMA,
    SEMICOLON,

    // 输入结束标记
    EOF
}
