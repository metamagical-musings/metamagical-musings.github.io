@echo off
echo Redirect URLs embedded in PDF files in the current folder
echo which point to the server at https://metamagical-musings.github.io 
echo so that they point to the current folder instead.
echo:
redirect.exe https://metamagical-musings.github.io
echo:
pause