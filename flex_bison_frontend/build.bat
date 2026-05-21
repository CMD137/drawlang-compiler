@echo off
setlocal

set "ROOT=%~dp0"
set "BUILD=%ROOT%build"
set "SRC=%ROOT%src"
set "BISON=%BUILD%\win_bison.exe"
set "FLEX=%BUILD%\win_flex.exe"
set "GCC=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe"
set "TOOL_DATA=%BUILD%\data"

set "PARSER_C=%BUILD%\flex_bison_frontend_parser.tab.c"
set "LEXER_C=%BUILD%\flex_bison_frontend_lexer.yy.c"
set "EXE=%BUILD%\flex_bison_frontend.exe"

if not exist "%BUILD%" mkdir "%BUILD%"

if not exist "%BISON%" goto missing_bison
if not exist "%FLEX%" goto missing_flex
if not exist "%GCC%" goto missing_gcc
if not exist "%TOOL_DATA%" goto missing_data

set "BISON_PKGDATADIR=%TOOL_DATA%"
set "FLEX_PKGDATADIR=%TOOL_DATA%"

echo [1/3] Generating parser...
"%BISON%" -d -o "%PARSER_C%" "%SRC%\drawlang_parser.y"
if errorlevel 1 goto failed

echo [2/3] Generating lexer...
"%FLEX%" -o "%LEXER_C%" "%SRC%\drawlang_lexer.l"
if errorlevel 1 goto failed

echo [3/3] Compiling executable...
"%GCC%" -I"%BUILD%" -o "%EXE%" "%PARSER_C%" "%LEXER_C%" -lm
if errorlevel 1 goto failed

echo [Build Success] %EXE%
endlocal
exit /b 0

:missing_bison
echo [Build Error] Missing build\win_bison.exe
endlocal
exit /b 1

:missing_flex
echo [Build Error] Missing build\win_flex.exe
endlocal
exit /b 1

:missing_gcc
echo [Build Error] Missing C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe
endlocal
exit /b 1

:missing_data
echo [Build Error] Missing build\data
echo Copy the win_flex_bison data folder into build\data.
endlocal
exit /b 1

:failed
echo [Build Error] Build failed.
endlocal
exit /b 1
