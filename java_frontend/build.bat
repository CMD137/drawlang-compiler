@echo off
setlocal

set "ROOT=%~dp0"
set "SRC=%ROOT%src"
set "BUILD=%ROOT%build"
set "CLASSES=%BUILD%\classes"
set "JAR=%BUILD%\java_frontend.jar"

if not exist "%BUILD%" mkdir "%BUILD%"
if not exist "%CLASSES%" mkdir "%CLASSES%"

echo [1/2] Compiling Java frontend...
pushd "%SRC%"
javac -encoding UTF-8 -d "%CLASSES%" ^
    drawlang\app\*.java ^
    drawlang\ast\*.java ^
    drawlang\lexer\*.java ^
    drawlang\parser\*.java
popd
if errorlevel 1 goto failed

echo [2/2] Packaging jar...
jar cfe "%JAR%" drawlang.app.Main -C "%CLASSES%" .
if errorlevel 1 goto failed

echo [Build Success] %JAR%
endlocal
exit /b 0

:failed
echo [Build Error] Build failed.
endlocal
exit /b 1
