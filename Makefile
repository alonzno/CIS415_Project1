part1: src/part1.l include/ll_1.h
	lex src/part1.l
	mv lex.yy.c build/part1.c
	gcc -o part1 build/part1.c include/ll_1.h
