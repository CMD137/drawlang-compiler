/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"

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


#line 189 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "flex_bison_frontend_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LINE = 3,                       /* LINE  */
  YYSYMBOL_RECT = 4,                       /* RECT  */
  YYSYMBOL_CIRCLE = 5,                     /* CIRCLE  */
  YYSYMBOL_TEXT = 6,                       /* TEXT  */
  YYSYMBOL_LPAREN = 7,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 8,                     /* RPAREN  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_SEMICOLON = 10,                 /* SEMICOLON  */
  YYSYMBOL_COLOR = 11,                     /* COLOR  */
  YYSYMBOL_WIDTH = 12,                     /* WIDTH  */
  YYSYMBOL_FILL = 13,                      /* FILL  */
  YYSYMBOL_NOFILL = 14,                    /* NOFILL  */
  YYSYMBOL_SIZE = 15,                      /* SIZE  */
  YYSYMBOL_NUMBER = 16,                    /* NUMBER  */
  YYSYMBOL_STRING = 17,                    /* STRING  */
  YYSYMBOL_IDENTIFIER = 18,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 19,                  /* $accept  */
  YYSYMBOL_program = 20,                   /* program  */
  YYSYMBOL_stmt_list = 21,                 /* stmt_list  */
  YYSYMBOL_statement = 22,                 /* statement  */
  YYSYMBOL_line_stmt = 23,                 /* line_stmt  */
  YYSYMBOL_rect_stmt = 24,                 /* rect_stmt  */
  YYSYMBOL_rect_fill_part = 25,            /* rect_fill_part  */
  YYSYMBOL_circle_stmt = 26,               /* circle_stmt  */
  YYSYMBOL_circle_fill_part = 27,          /* circle_fill_part  */
  YYSYMBOL_text_stmt = 28,                 /* text_stmt  */
  YYSYMBOL_number = 29,                    /* number  */
  YYSYMBOL_string = 30,                    /* string  */
  YYSYMBOL_color_name = 31                 /* color_name  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   64

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  19
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  19
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  76

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   145,   145,   153,   159,   165,   169,   173,   177,   184,
     192,   200,   204,   211,   219,   223,   230,   238,   245,   252
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LINE", "RECT",
  "CIRCLE", "TEXT", "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "COLOR",
  "WIDTH", "FILL", "NOFILL", "SIZE", "NUMBER", "STRING", "IDENTIFIER",
  "$accept", "program", "stmt_list", "statement", "line_stmt", "rect_stmt",
  "rect_fill_part", "circle_stmt", "circle_fill_part", "text_stmt",
  "number", "string", "color_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -41,     5,    24,   -41,     0,    12,    13,    14,   -41,   -41,
     -41,   -41,   -41,     7,     7,     7,     7,   -41,    15,    23,
      25,    26,     7,     7,     7,     7,    27,    28,    29,    30,
       7,     7,     7,    16,    33,    34,    36,   -41,    37,     7,
       7,    38,    39,    40,    43,    35,    35,    41,    44,   -41,
      42,    45,    35,    35,     7,     7,    46,    47,   -10,    51,
       7,     7,    35,   -41,    52,   -41,    53,     1,   -41,   -41,
     -41,    35,   -41,    54,   -41,   -41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     3,     5,
       6,     7,     8,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,    16,     0,     0,    14,    13,
       9,     0,    12,     0,    11,    10
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -14,   -41,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    10,    73,    11,    64,    12,
      18,    38,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    20,    21,    62,    63,     3,    51,    13,    26,    27,
      28,    29,    56,    57,    71,    72,    34,    35,    36,    14,
      15,    16,    68,    17,    22,    43,    44,     4,     5,     6,
       7,    74,    23,    37,    24,    25,    30,    31,    32,    33,
      58,    59,    39,    40,    41,    42,    66,    67,    47,    45,
      46,    48,    52,    49,    54,    53,     0,     0,    60,    61,
      55,    65,    69,    70,    75
};

static const yytype_int8 yycheck[] =
{
      14,    15,    16,    13,    14,     0,    46,     7,    22,    23,
      24,    25,    52,    53,    13,    14,    30,    31,    32,     7,
       7,     7,    62,    16,     9,    39,    40,     3,     4,     5,
       6,    71,     9,    17,     9,     9,     9,     9,     9,     9,
      54,    55,     9,     9,     8,     8,    60,    61,     8,    11,
      11,     8,    11,    18,    12,    11,    -1,    -1,    12,    12,
      15,    10,    10,    10,    10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    21,     0,     3,     4,     5,     6,    22,    23,
      24,    26,    28,     7,     7,     7,     7,    16,    29,    29,
      29,    29,     9,     9,     9,     9,    29,    29,    29,    29,
       9,     9,     9,     9,    29,    29,    29,    17,    30,     9,
       9,     8,     8,    29,    29,    11,    11,     8,     8,    18,
      31,    31,    11,    11,    12,    15,    31,    31,    29,    29,
      12,    12,    13,    14,    27,    10,    29,    29,    31,    10,
      10,    13,    14,    25,    31,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    19,    20,    21,    21,    22,    22,    22,    22,    23,
      24,    25,    25,    26,    27,    27,    28,    29,    30,    31
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,    15,
      16,     2,     1,    14,     2,     1,    13,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 146 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        g_program_result = (yyvsp[0].program);
        (yyval.program) = (yyvsp[0].program);
    }
#line 1627 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 3: /* stmt_list: stmt_list statement  */
#line 154 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          program_add((yyvsp[-1].program), (yyvsp[0].command));
          (yyval.program) = (yyvsp[-1].program);
      }
#line 1636 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 4: /* stmt_list: %empty  */
#line 159 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.program) = program_create();
      }
#line 1644 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 5: /* statement: line_stmt  */
#line 166 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.command) = (yyvsp[0].command);
      }
#line 1652 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 6: /* statement: rect_stmt  */
#line 170 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.command) = (yyvsp[0].command);
      }
#line 1660 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 7: /* statement: circle_stmt  */
#line 174 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.command) = (yyvsp[0].command);
      }
#line 1668 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 8: /* statement: text_stmt  */
#line 178 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.command) = (yyvsp[0].command);
      }
#line 1676 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 9: /* line_stmt: LINE LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number SEMICOLON  */
#line 186 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.command) = command_create_line((yyvsp[-12].number), (yyvsp[-10].number), (yyvsp[-8].number), (yyvsp[-6].number), (yyvsp[-3].text), (yyvsp[-1].number));
    }
#line 1684 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 10: /* rect_stmt: RECT LPAREN number COMMA number COMMA number COMMA number RPAREN COLOR color_name WIDTH number rect_fill_part SEMICOLON  */
#line 194 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.command) = command_create_rect((yyvsp[-13].number), (yyvsp[-11].number), (yyvsp[-9].number), (yyvsp[-7].number), (yyvsp[-4].text), (yyvsp[-2].number), (yyvsp[-1].fill));
    }
#line 1692 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 11: /* rect_fill_part: FILL color_name  */
#line 201 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.fill) = fill_spec_create(1, (yyvsp[0].text));
      }
#line 1700 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 12: /* rect_fill_part: NOFILL  */
#line 205 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.fill) = fill_spec_create(0, NULL);
      }
#line 1708 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 13: /* circle_stmt: CIRCLE LPAREN number COMMA number COMMA number RPAREN COLOR color_name WIDTH number circle_fill_part SEMICOLON  */
#line 213 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.command) = command_create_circle((yyvsp[-11].number), (yyvsp[-9].number), (yyvsp[-7].number), (yyvsp[-4].text), (yyvsp[-2].number), (yyvsp[-1].fill));
    }
#line 1716 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 14: /* circle_fill_part: FILL color_name  */
#line 220 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.fill) = fill_spec_create(1, (yyvsp[0].text));
      }
#line 1724 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 15: /* circle_fill_part: NOFILL  */
#line 224 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
      {
          (yyval.fill) = fill_spec_create(0, NULL);
      }
#line 1732 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 16: /* text_stmt: TEXT LPAREN number COMMA number COMMA string RPAREN COLOR color_name SIZE number SEMICOLON  */
#line 232 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.command) = command_create_text((yyvsp[-10].number), (yyvsp[-8].number), (yyvsp[-6].text), (yyvsp[-3].text), (yyvsp[-1].number));
    }
#line 1740 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 17: /* number: NUMBER  */
#line 239 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.number) = (yyvsp[0].number);
    }
#line 1748 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 18: /* string: STRING  */
#line 246 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.text) = (yyvsp[0].text);
    }
#line 1756 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;

  case 19: /* color_name: IDENTIFIER  */
#line 253 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"
    {
        (yyval.text) = (yyvsp[0].text);
    }
#line 1764 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"
    break;


#line 1768 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\build\\flex_bison_frontend_parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 258 "C:\\Users\\29924\\Desktop\\文档\\大三\\编译原理\\ks\\flex_bison_frontend\\src\\drawlang_parser.y"


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
