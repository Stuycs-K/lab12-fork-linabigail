.PHONY: compile run clean
compile main:
	@gcc -o main main.c
run:
	@./main
clean:
	@rm -f *.o main
