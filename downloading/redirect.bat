@echo off
echo Redirect URLs embedded in PDF files in the parent folder
echo which point to the server at https://metamagical-musings.github.io 
echo so that they point to the parent folder instead.
echo:
cd "%~dp0.."
"%~dp0redirect.exe" https://metamagical-musings.github.io
echo:
pause