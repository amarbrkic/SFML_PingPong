@REM if debug or release

@echo off

if "%1" == "debug" (
    devenv.com SFML_PingPong.sln /build Debug
    cd x64\Debug
    SFML_PingPong.exe
    cd ..\..
) else if "%1" == "release" (
    
    cd ..
    xcopy /s /i /q /y SFML_PingPong\* "C:\Users\amarb\Desktop\SFML_PingPong"
    devenv.com C:\Users\amarb\Desktop\SFML_PingPong\SFML_PingPong.sln /build Release
    C:\Users\amarb\Desktop\SFML_PingPong\x64\Release\SFML_PingPong.exe
    @REM and copy the whole Release directory to the SFML_PingPong directory
    xcopy /s /i /q /y C:\Users\amarb\Desktop\SFML_PingPong\x64\Release\* SFML_PingPong\x64\Release
) else (
    echo "Usage: build.bat [debug|release]"
    exit 1
)