%option noyywrap nounput noinput never-interactive

%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FillSpec FillSpec;
typedef struct Command Command;
typedef struct Program Program;

#include "drawlang_parser.tab.h"

int g_has_lexical_error = 0;
char g_error_message[1024];
int g_lexer_line = 1;
int g_lexer_column = 1;

static int g_string_start_line = 1;
static int g_string_start_column = 1;
static char *g_string_buffer = NULL;
static size_t g_string_length = 0U;
static size_t g_string_capacity = 0U;

static void update_position(const char *text, int length);
static void update_position_with_location(const char *text, int length, YYLTYPE *location,
                                          int first_line, int first_column);
static void set_empty_location(YYLTYPE *location);
static char *dup_range(const char *text, size_t length);
static int lookup_keyword(const char *text);
static void report_lexical_error(int line, int column, const char *message);
static void string_reset(void);
static void string_append(const char *text, size_t length);

void drawlang_reset_lexer_state(void);
%}

%x STRING_STATE

%%

[ \t\r\n]+ {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
}

"//".* {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
}

"(" {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    return LPAREN;
}

")" {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    return RPAREN;
}

"," {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    return COMMA;
}

";" {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    return SEMICOLON;
}

\" {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
    string_reset();
    g_string_start_line = start_line;
    g_string_start_column = start_column;
    BEGIN(STRING_STATE);
}

[+-]\.[0-9]+ {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    yylval.number = strtod(yytext, NULL);
    return NUMBER;
}

[+-]?[0-9]+(\.[0-9]*)? {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    yylval.number = strtod(yytext, NULL);
    return NUMBER;
}

[+-]\. {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    report_lexical_error(start_line, start_column, "invalid number ");
    return 0;
}

[A-Za-z_][A-Za-z0-9_]* {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    int token_type;

    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    token_type = lookup_keyword(yytext);
    if (token_type != IDENTIFIER) {
        return token_type;
    }

    yylval.text = dup_range(yytext, (size_t) yyleng);
    return IDENTIFIER;
}

. {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    char message[128];

    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    snprintf(message, sizeof(message), "illegal character '%c'", yytext[0]);
    report_lexical_error(start_line, start_column, message);
    return 0;
}

<STRING_STATE>[^"\r\n]+ {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
    string_append(yytext, (size_t) yyleng);
}

<STRING_STATE>\" {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;

    update_position_with_location(yytext, yyleng, &yylloc, start_line, start_column);
    yylloc.first_line = g_string_start_line;
    yylloc.first_column = g_string_start_column;
    yylval.text = dup_range(g_string_buffer, g_string_length);
    string_reset();
    BEGIN(INITIAL);
    return STRING;
}

<STRING_STATE>\r\n {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
    report_lexical_error(g_string_start_line, g_string_start_column, "not found right \"");
    string_reset();
    BEGIN(INITIAL);
    return 0;
}

<STRING_STATE>\r {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
    report_lexical_error(g_string_start_line, g_string_start_column, "not found right \"");
    string_reset();
    BEGIN(INITIAL);
    return 0;
}

<STRING_STATE>\n {
    int start_line = g_lexer_line;
    int start_column = g_lexer_column;
    update_position_with_location(yytext, yyleng, NULL, start_line, start_column);
    report_lexical_error(g_string_start_line, g_string_start_column, "not found right \"");
    string_reset();
    BEGIN(INITIAL);
    return 0;
}

<STRING_STATE><<EOF>> {
    report_lexical_error(g_string_start_line, g_string_start_column, "not found right \"");
    string_reset();
    BEGIN(INITIAL);
    set_empty_location(&yylloc);
    return 0;
}

<<EOF>> {
    set_empty_location(&yylloc);
    return 0;
}

%%

void drawlang_reset_lexer_state(void) {
    g_has_lexical_error = 0;
    g_error_message[0] = '\0';
    g_lexer_line = 1;
    g_lexer_column = 1;
    g_string_start_line = 1;
    g_string_start_column = 1;
    string_reset();
    BEGIN(INITIAL);
}

static void update_position(const char *text, int length) {
    int i;

    for (i = 0; i < length; i++) {
        if (text[i] == '\n') {
            g_lexer_line++;
            g_lexer_column = 1;
        } else {
            g_lexer_column++;
        }
    }
}

static void update_position_with_location(const char *text, int length, YYLTYPE *location,
                                          int first_line, int first_column) {
    int i;
    int current_line;
    int current_column;
    int last_line;
    int last_column;

    current_line = first_line;
    current_column = first_column;
    last_line = first_line;
    last_column = first_column;

    for (i = 0; i < length; i++) {
        last_line = current_line;
        last_column = current_column;
        if (text[i] == '\n') {
            current_line++;
            current_column = 1;
        } else {
            current_column++;
        }
    }

    if (location != NULL) {
        location->first_line = first_line;
        location->first_column = first_column;
        location->last_line = last_line;
        location->last_column = last_column;
    }

    g_lexer_line = current_line;
    g_lexer_column = current_column;
}

static void set_empty_location(YYLTYPE *location) {
    location->first_line = g_lexer_line;
    location->first_column = g_lexer_column;
    location->last_line = g_lexer_line;
    location->last_column = g_lexer_column;
}

static char *dup_range(const char *text, size_t length) {
    char *copy;

    copy = (char *) malloc(length + 1U);
    if (copy == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }

    memcpy(copy, text, length);
    copy[length] = '\0';
    return copy;
}

static int lookup_keyword(const char *text) {
    char upper[64];
    size_t i;
    size_t length;

    length = strlen(text);
    if (length >= sizeof(upper)) {
        return IDENTIFIER;
    }

    for (i = 0U; i < length; i++) {
        upper[i] = (char) toupper((unsigned char) text[i]);
    }
    upper[length] = '\0';

    if (strcmp(upper, "LINE") == 0) {
        return LINE;
    }
    if (strcmp(upper, "RECT") == 0) {
        return RECT;
    }
    if (strcmp(upper, "CIRCLE") == 0) {
        return CIRCLE;
    }
    if (strcmp(upper, "TEXT") == 0) {
        return TEXT;
    }
    if (strcmp(upper, "COLOR") == 0) {
        return COLOR;
    }
    if (strcmp(upper, "WIDTH") == 0) {
        return WIDTH;
    }
    if (strcmp(upper, "FILL") == 0) {
        return FILL;
    }
    if (strcmp(upper, "NOFILL") == 0) {
        return NOFILL;
    }
    if (strcmp(upper, "SIZE") == 0) {
        return SIZE;
    }

    return IDENTIFIER;
}

static void report_lexical_error(int line, int column, const char *message) {
    g_has_lexical_error = 1;
    snprintf(
        g_error_message,
        sizeof(g_error_message),
        "[Error][Lexical] line %d, col %d: %s",
        line,
        column,
        message
    );
}

static void string_reset(void) {
    free(g_string_buffer);
    g_string_buffer = NULL;
    g_string_length = 0U;
    g_string_capacity = 0U;
}

static void string_append(const char *text, size_t length) {
    size_t required;

    required = g_string_length + length + 1U;
    if (required > g_string_capacity) {
        size_t new_capacity;
        char *new_buffer;

        new_capacity = g_string_capacity == 0U ? 32U : g_string_capacity;
        while (new_capacity < required) {
            new_capacity *= 2U;
        }

        new_buffer = (char *) realloc(g_string_buffer, new_capacity);
        if (new_buffer == NULL) {
            fprintf(stderr, "Out of memory.\n");
            exit(1);
        }
        g_string_buffer = new_buffer;
        g_string_capacity = new_capacity;
    }

    memcpy(g_string_buffer + g_string_length, text, length);
    g_string_length += length;
    g_string_buffer[g_string_length] = '\0';
}
