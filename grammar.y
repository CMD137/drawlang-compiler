%define lr.type canonical-lr
%define parse.error verbose

%token LINE RECT CIRCLE TEXT
%token LPAREN RPAREN COMMA SEMICOLON
%token COLOR WIDTH FILL NOFILL SIZE
%token NUMBER STRING IDENTIFIER

%%

program:
    stmt_list
;

stmt_list:
      stmt_list statement
    | /* empty */
;

statement:
      line_stmt
    | rect_stmt
    | circle_stmt
    | text_stmt
;

line_stmt:
    LINE LPAREN number COMMA number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number SEMICOLON
;

rect_stmt:
    RECT LPAREN number COMMA number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number rect_fill_part SEMICOLON
;

rect_fill_part:
      FILL color_name
    | NOFILL
;

circle_stmt:
    CIRCLE LPAREN number COMMA number COMMA number RPAREN
    COLOR color_name WIDTH number circle_fill_part SEMICOLON
;

circle_fill_part:
      FILL color_name
    | NOFILL
;

text_stmt:
    TEXT LPAREN number COMMA number COMMA string RPAREN
    COLOR color_name SIZE number SEMICOLON
;

number:
    NUMBER
;

string:
    STRING
;

color_name:
    IDENTIFIER
;

%%
