# Makefile for Gitignore Adder

build:
	gcc main.c oscore.c oscore.h -o main

run:
	$(MAKE) build
	./main

