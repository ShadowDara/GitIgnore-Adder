@echo off

echo Building Gitignore Adder with Zig for Windows

zig cc -Os main.c oscore.c -o gitignore-adder.exe
