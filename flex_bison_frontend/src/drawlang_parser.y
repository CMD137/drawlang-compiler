%{
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum CommandType {
    CMD_LINE,
    CMD_RECT,
    CMD_CIRCLE,
    CMD_TEXT
} CommandType;

typedef struct FillSpec {
    int has_fill;
    char *fill_color;
} FillSpec;

typedef struct LineData {
    double x1;
    double y1;
    double x2;
    double y2;
    char *color;
    double line_width;
} LineData;

typedef struct RectData {
    double x;
    double y;
    double width;
    double height;
    char *color;
    double line_width;
    FillSpec *fill;
} RectData;

typedef struct CircleData {
    double cx;
    double cy;
    double radius;
    char *color;
    double line_width;
    FillSpec *fill;
} CircleData;

typedef struct TextData {
    double x;
    double y;
    char *content;
    char *color;
    double font_size;
} TextData;

typedef struct Command {
    CommandType type;
    union {
        LineData line;
        RectData rect;
        CircleData circle;
        TextData text;
    } data;
} Command;

typedef struct Program {
    Command **commands;
    size_t count;
    size_t capacity;
} Program;

static Program *program_create(void);
static void program_add(Program *program, Command *command);
static void program_free(Program *program);

static FillSpec *fill_spec_create(int has_fill, char *fill_color);
static void fill_spec_free(FillSpec *fill);

static Command *command_create_line(double x1, double y1, double x2, double y2,
                                    char *color, double line_width);
static Command *command_create_rect(double x, double y, double width, double height,
                                    char *color, double line_width, FillSpec *fill);
static Command *command_create_circle(double cx, double cy, double radius,
                                      char *color, double line_width, FillSpec *fill);
static Command *command_create_text(double x, double y, char *content,
                                    char *color, double font_size);
static void command_free(Command *command);

static char *dl_strdup(const char *text);
static void *dl_xmalloc(size_t size);
static void *dl_xrealloc(void *ptr, size_t size);

static void print_ast_summary(const char *input_path, const Program *program);
static void print_json_ir(const Program *program);
static void print_ast_command(size_t index, const Command *command);
static void print_json_command(const Command *command, int has_next);
static void print_ast_number(double value);
static void print_json_number(double value);
static void print_json_string(const char *text);
static int is_integer_like(double value);

static int has_draw_extension(const char *path);
static void reset_driver_state(void);
static void normalize_expected_list(char *text);
static void store_syntax_error(const char *message, int line, int column);
void yyerror(const char *message);

extern FILE *yyin;
extern int yylex(void);
extern int g_has_lexical_error;
extern char g_error_message[1024];
void drawlang_reset_lexer_state(void);

Program *g_program_result = NULL;
int g_has_syntax_error = 0;

%}

%locations
%define parse.error verbose

%union {
    double number;
    char *text;
    FillSpec *fill;
    Command *command;
    Program *program;
}

%token LINE RECT CIRCLE TEXT
%token LPAREN RPAREN COMMA SEMICOLON
%token COLOR WIDTH FILL NOFILL SIZE
%token <number> NUMBER
%token <text> STRING IDENTIFIER

%type <program> program stmt_list
%type <command> statement line_stmt rect_stmt circle_stmt text_stmt
%type <fill> rect_fill_part circle_fill_part
%type <number> number
%type <text> string color_name

%%

program:
    stmt_list
    {
        g_program_result = $1;
        $$ = $1;
    }
;

stmt_list:
      stmt_list statement
      {
          program_add($1, $2);
          $$ = $1;
      }
    | /* empty */
      {
          $$ = program_create();
      }
;

statement:
      line_stmt
      {
          $$ = $1;
      }
    | rect_stmt
      {
          $$ = $1;
      }
    | circle_stmt
      {
          $$ = $1;
      }
    | text_stmt
      {
          $$ = $1;
      }
;

line_stmt:
    LINE LPAREN number COMMA number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number SEMICOLON
    {
        $$ = command_create_line($3, $5, $7, $9, $12, $14);
    }
;

rect_stmt:
    RECT LPAREN number COMMA number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number rect_fill_part SEMICOLON
    {
        $$ = command_create_rect($3, $5, $7, $9, $12, $14, $15);
    }
;

rect_fill_part:
      FILL color_name
      {
          $$ = fill_spec_create(1, $2);
      }
    | NOFILL
      {
          $$ = fill_spec_create(0, NULL);
      }
;

circle_stmt:
    CIRCLE LPAREN number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number circle_fill_part SEMICOLON
    {
        $$ = command_create_circle($3, $5, $7, $10, $12, $13);
    }
;

circle_fill_part:
      FILL color_name
      {
          $$ = fill_spec_create(1, $2);
      }
    | NOFILL
      {
          $$ = fill_spec_create(0, NULL);
      }
;

text_stmt:
    TEXT LPAREN number COMMA number COMMA string RPAREN
    COLOR color_name SIZE number SEMICOLON
    {
        $$ = command_create_text($3, $5, $7, $10, $12);
    }
;

number:
    NUMBER
    {
        $$ = $1;
    }
;

string:
    STRING
    {
        $$ = $1;
    }
;

color_name:
    IDENTIFIER
    {
        $$ = $1;
    }
;

%%

void yyerror(const char *message) {
    if (g_has_lexical_error) {
        return;
    }
    store_syntax_error(message, yylloc.first_line, yylloc.first_column);
}

int main(int argc, char **argv) {
    const char *input_path;
    FILE *input_file;
    int parse_result;

    input_path = argc > 1 ? argv[1] : "samples/test.draw";

    if (!has_draw_extension(input_path)) {
        printf("[Input Error] Input file must use the .draw extension: %s\n", input_path);
        return 1;
    }

    input_file = fopen(input_path, "rb");
    if (input_file == NULL) {
        printf("[Input Error] File not found: %s\n", input_path);
        return 1;
    }

    yyin = input_file;
    reset_driver_state();
    parse_result = yyparse();
    fclose(input_file);

    if (g_has_lexical_error || g_has_syntax_error || parse_result != 0) {
        if (g_error_message[0] != '\0') {
            puts(g_error_message);
        }
        program_free(g_program_result);
        return 1;
    }

    print_ast_summary(input_path, g_program_result);
    puts("");
    print_json_ir(g_program_result);
    program_free(g_program_result);
    g_program_result = NULL;
    return 0;
}

static void reset_driver_state(void) {
    g_program_result = NULL;
    g_has_syntax_error = 0;
    g_has_lexical_error = 0;
    g_error_message[0] = '\0';
    drawlang_reset_lexer_state();
}

static int has_draw_extension(const char *path) {
    size_t length;
    const char *suffix;
    int i;
    static const char expected[] = ".draw";

    if (path == NULL) {
        return 0;
    }

    length = strlen(path);
    if (length < sizeof(expected) - 1U) {
        return 0;
    }

    suffix = path + length - (sizeof(expected) - 1U);
    for (i = 0; expected[i] != '\0'; i++) {
        if (tolower((unsigned char) suffix[i]) != expected[i]) {
            return 0;
        }
    }
    return 1;
}

static void store_syntax_error(const char *message, int line, int column) {
    const char *prefix_a = "syntax error, unexpected ";
    const char *prefix_b = "parse error, unexpected ";
    const char *prefix;
    const char *actual_start;
    const char *expected_start;
    size_t prefix_length;
    size_t actual_length;
    char actual[256];
    char expected[512];

    prefix = NULL;
    if (strncmp(message, prefix_a, strlen(prefix_a)) == 0) {
        prefix = prefix_a;
    } else if (strncmp(message, prefix_b, strlen(prefix_b)) == 0) {
        prefix = prefix_b;
    }

    if (prefix == NULL) {
        snprintf(
            g_error_message,
            sizeof(g_error_message),
            "[Error][Syntax ] line %d, col %d: %s",
            line,
            column,
            message
        );
        g_has_syntax_error = 1;
        return;
    }

    prefix_length = strlen(prefix);
    actual_start = message + prefix_length;
    expected_start = strstr(actual_start, ", expecting ");

    if (expected_start == NULL) {
        snprintf(
            g_error_message,
            sizeof(g_error_message),
            "[Error][Syntax ] line %d, col %d: unexpected token %s",
            line,
            column,
            actual_start
        );
        g_has_syntax_error = 1;
        return;
    }

    actual_length = (size_t) (expected_start - actual_start);
    if (actual_length >= sizeof(actual)) {
        actual_length = sizeof(actual) - 1U;
    }
    memcpy(actual, actual_start, actual_length);
    actual[actual_length] = '\0';

    strncpy(expected, expected_start + 12, sizeof(expected) - 1U);
    expected[sizeof(expected) - 1U] = '\0';
    normalize_expected_list(expected);

    snprintf(
        g_error_message,
        sizeof(g_error_message),
        "[Error][Syntax ] line %d, col %d: unexpected token %s, expected %s",
        line,
        column,
        actual,
        expected
    );
    g_has_syntax_error = 1;
}

static void normalize_expected_list(char *text) {
    char buffer[512];
    char *original;
    char *out;

    if (strcmp(text, "end of file") == 0) {
        strcpy(text, "LINE, RECT, CIRCLE, TEXT, EOF");
        return;
    }

    original = text;
    out = buffer;
    while (*text != '\0' && (size_t) (out - buffer) < sizeof(buffer) - 1U) {
        if (strncmp(text, " or ", 4) == 0) {
            *out++ = ',';
            *out++ = ' ';
            text += 4;
            continue;
        }
        *out++ = *text++;
    }
    *out = '\0';

    strcpy(original, buffer);
}

static void *dl_xmalloc(size_t size) {
    void *ptr;

    ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    return ptr;
}

static void *dl_xrealloc(void *ptr, size_t size) {
    void *new_ptr;

    new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    return new_ptr;
}

static char *dl_strdup(const char *text) {
    size_t length;
    char *copy;

    if (text == NULL) {
        return NULL;
    }

    length = strlen(text);
    copy = (char *) dl_xmalloc(length + 1U);
    memcpy(copy, text, length + 1U);
    return copy;
}

static Program *program_create(void) {
    Program *program;

    program = (Program *) dl_xmalloc(sizeof(Program));
    program->commands = NULL;
    program->count = 0U;
    program->capacity = 0U;
    return program;
}

static void program_add(Program *program, Command *command) {
    size_t new_capacity;

    if (program->count == program->capacity) {
        new_capacity = program->capacity == 0U ? 4U : program->capacity * 2U;
        program->commands = (Command **) dl_xrealloc(
            program->commands,
            new_capacity * sizeof(Command *)
        );
        program->capacity = new_capacity;
    }

    program->commands[program->count++] = command;
}

static void program_free(Program *program) {
    size_t i;

    if (program == NULL) {
        return;
    }

    for (i = 0U; i < program->count; i++) {
        command_free(program->commands[i]);
    }
    free(program->commands);
    free(program);
}

static FillSpec *fill_spec_create(int has_fill, char *fill_color) {
    FillSpec *fill;

    fill = (FillSpec *) dl_xmalloc(sizeof(FillSpec));
    fill->has_fill = has_fill;
    fill->fill_color = has_fill ? fill_color : NULL;
    if (!has_fill && fill_color != NULL) {
        free(fill_color);
    }
    return fill;
}

static void fill_spec_free(FillSpec *fill) {
    if (fill == NULL) {
        return;
    }
    free(fill->fill_color);
    free(fill);
}

static Command *command_create_line(double x1, double y1, double x2, double y2,
                                    char *color, double line_width) {
    Command *command;

    command = (Command *) dl_xmalloc(sizeof(Command));
    command->type = CMD_LINE;
    command->data.line.x1 = x1;
    command->data.line.y1 = y1;
    command->data.line.x2 = x2;
    command->data.line.y2 = y2;
    command->data.line.color = color;
    command->data.line.line_width = line_width;
    return command;
}

static Command *command_create_rect(double x, double y, double width, double height,
                                    char *color, double line_width, FillSpec *fill) {
    Command *command;

    command = (Command *) dl_xmalloc(sizeof(Command));
    command->type = CMD_RECT;
    command->data.rect.x = x;
    command->data.rect.y = y;
    command->data.rect.width = width;
    command->data.rect.height = height;
    command->data.rect.color = color;
    command->data.rect.line_width = line_width;
    command->data.rect.fill = fill;
    return command;
}

static Command *command_create_circle(double cx, double cy, double radius,
                                      char *color, double line_width, FillSpec *fill) {
    Command *command;

    command = (Command *) dl_xmalloc(sizeof(Command));
    command->type = CMD_CIRCLE;
    command->data.circle.cx = cx;
    command->data.circle.cy = cy;
    command->data.circle.radius = radius;
    command->data.circle.color = color;
    command->data.circle.line_width = line_width;
    command->data.circle.fill = fill;
    return command;
}

static Command *command_create_text(double x, double y, char *content,
                                    char *color, double font_size) {
    Command *command;

    command = (Command *) dl_xmalloc(sizeof(Command));
    command->type = CMD_TEXT;
    command->data.text.x = x;
    command->data.text.y = y;
    command->data.text.content = content;
    command->data.text.color = color;
    command->data.text.font_size = font_size;
    return command;
}

static void command_free(Command *command) {
    if (command == NULL) {
        return;
    }

    switch (command->type) {
        case CMD_LINE:
            free(command->data.line.color);
            break;
        case CMD_RECT:
            free(command->data.rect.color);
            fill_spec_free(command->data.rect.fill);
            break;
        case CMD_CIRCLE:
            free(command->data.circle.color);
            fill_spec_free(command->data.circle.fill);
            break;
        case CMD_TEXT:
            free(command->data.text.content);
            free(command->data.text.color);
            break;
    }

    free(command);
}

static int is_integer_like(double value) {
    double truncated;

    if (value == 0.0) {
        return 1;
    }

    truncated = floor(value);
    return fabs(value - truncated) < 1e-9;
}

static void print_ast_number(double value) {
    if (is_integer_like(value)) {
        printf("%.1f", value);
    } else {
        printf("%.15g", value);
    }
}

static void print_json_number(double value) {
    if (fabs(value) < 1e-12) {
        value = 0.0;
    }

    if (is_integer_like(value)) {
        printf("%.0f", value);
    } else {
        printf("%.15g", value);
    }
}

static void print_json_string(const char *text) {
    const unsigned char *cursor;

    putchar('"');
    cursor = (const unsigned char *) text;
    while (*cursor != '\0') {
        switch (*cursor) {
            case '"':
                printf("\\\"");
                break;
            case '\\':
                printf("\\\\");
                break;
            case '\b':
                printf("\\b");
                break;
            case '\f':
                printf("\\f");
                break;
            case '\n':
                printf("\\n");
                break;
            case '\r':
                printf("\\r");
                break;
            case '\t':
                printf("\\t");
                break;
            default:
                if (*cursor < 0x20U) {
                    printf("\\u%04x", (unsigned int) *cursor);
                } else {
                    putchar((int) *cursor);
                }
                break;
        }
        cursor++;
    }
    putchar('"');
}

static void print_ast_summary(const char *input_path, const Program *program) {
    size_t i;

    printf("[Parse Success] %s\n", input_path);
    printf("Command count: %lu\n", (unsigned long) program->count);

    for (i = 0U; i < program->count; i++) {
        print_ast_command(i + 1U, program->commands[i]);
    }
}

static void print_ast_command(size_t index, const Command *command) {
    printf("%lu. ", (unsigned long) index);

    switch (command->type) {
        case CMD_LINE:
            printf("LineNode{x1=");
            print_ast_number(command->data.line.x1);
            printf(", y1=");
            print_ast_number(command->data.line.y1);
            printf(", x2=");
            print_ast_number(command->data.line.x2);
            printf(", y2=");
            print_ast_number(command->data.line.y2);
            printf(", color='%s', lineWidth=", command->data.line.color);
            print_ast_number(command->data.line.line_width);
            printf("}\n");
            break;
        case CMD_RECT:
            printf("RectNode{x=");
            print_ast_number(command->data.rect.x);
            printf(", y=");
            print_ast_number(command->data.rect.y);
            printf(", width=");
            print_ast_number(command->data.rect.width);
            printf(", height=");
            print_ast_number(command->data.rect.height);
            printf(", color='%s', lineWidth=", command->data.rect.color);
            print_ast_number(command->data.rect.line_width);
            printf(", fill=FillSpec{hasFill=%s, fillColor='%s'}}\n",
                   command->data.rect.fill->has_fill ? "true" : "false",
                   command->data.rect.fill->has_fill ? command->data.rect.fill->fill_color : "null");
            break;
        case CMD_CIRCLE:
            printf("CircleNode{cx=");
            print_ast_number(command->data.circle.cx);
            printf(", cy=");
            print_ast_number(command->data.circle.cy);
            printf(", radius=");
            print_ast_number(command->data.circle.radius);
            printf(", color='%s', lineWidth=", command->data.circle.color);
            print_ast_number(command->data.circle.line_width);
            printf(", fill=FillSpec{hasFill=%s, fillColor='%s'}}\n",
                   command->data.circle.fill->has_fill ? "true" : "false",
                   command->data.circle.fill->has_fill ? command->data.circle.fill->fill_color : "null");
            break;
        case CMD_TEXT:
            printf("TextNode{x=");
            print_ast_number(command->data.text.x);
            printf(", y=");
            print_ast_number(command->data.text.y);
            printf(", content='%s', color='%s', fontSize=",
                   command->data.text.content,
                   command->data.text.color);
            print_ast_number(command->data.text.font_size);
            printf("}\n");
            break;
    }
}

static void print_json_ir(const Program *program) {
    size_t i;

    puts("[JSON IR]");
    puts("{");
    puts("  \"commands\": [");
    for (i = 0U; i < program->count; i++) {
        print_json_command(program->commands[i], i + 1U < program->count);
    }
    puts("  ]");
    puts("}");
}

static void print_json_command(const Command *command, int has_next) {
    printf("    {\n");

    switch (command->type) {
        case CMD_LINE:
            printf("      \"type\": \"line\",\n");
            printf("      \"x1\": ");
            print_json_number(command->data.line.x1);
            printf(",\n      \"y1\": ");
            print_json_number(command->data.line.y1);
            printf(",\n      \"x2\": ");
            print_json_number(command->data.line.x2);
            printf(",\n      \"y2\": ");
            print_json_number(command->data.line.y2);
            printf(",\n      \"color\": ");
            print_json_string(command->data.line.color);
            printf(",\n      \"lineWidth\": ");
            print_json_number(command->data.line.line_width);
            printf("\n");
            break;
        case CMD_RECT:
            printf("      \"type\": \"rect\",\n");
            printf("      \"x\": ");
            print_json_number(command->data.rect.x);
            printf(",\n      \"y\": ");
            print_json_number(command->data.rect.y);
            printf(",\n      \"width\": ");
            print_json_number(command->data.rect.width);
            printf(",\n      \"height\": ");
            print_json_number(command->data.rect.height);
            printf(",\n      \"color\": ");
            print_json_string(command->data.rect.color);
            printf(",\n      \"lineWidth\": ");
            print_json_number(command->data.rect.line_width);
            printf(",\n      \"fill\": ");
            if (command->data.rect.fill->has_fill) {
                print_json_string(command->data.rect.fill->fill_color);
            } else {
                printf("null");
            }
            printf("\n");
            break;
        case CMD_CIRCLE:
            printf("      \"type\": \"circle\",\n");
            printf("      \"cx\": ");
            print_json_number(command->data.circle.cx);
            printf(",\n      \"cy\": ");
            print_json_number(command->data.circle.cy);
            printf(",\n      \"radius\": ");
            print_json_number(command->data.circle.radius);
            printf(",\n      \"color\": ");
            print_json_string(command->data.circle.color);
            printf(",\n      \"lineWidth\": ");
            print_json_number(command->data.circle.line_width);
            printf(",\n      \"fill\": ");
            if (command->data.circle.fill->has_fill) {
                print_json_string(command->data.circle.fill->fill_color);
            } else {
                printf("null");
            }
            printf("\n");
            break;
        case CMD_TEXT:
            printf("      \"type\": \"text\",\n");
            printf("      \"x\": ");
            print_json_number(command->data.text.x);
            printf(",\n      \"y\": ");
            print_json_number(command->data.text.y);
            printf(",\n      \"content\": ");
            print_json_string(command->data.text.content);
            printf(",\n      \"color\": ");
            print_json_string(command->data.text.color);
            printf(",\n      \"fontSize\": ");
            print_json_number(command->data.text.font_size);
            printf("\n");
            break;
    }

    printf("    }");
    if (has_next) {
        printf(",");
    }
    printf("\n");
}
