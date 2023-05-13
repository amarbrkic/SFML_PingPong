@REM delete x64 folder and its contents
@RD /S /Q x64
@REM delete SFML_PingPong/x64 folder and its contents
@RD /S /Q SFML_PingPong\x64

git add .
git commit -m "."
git push