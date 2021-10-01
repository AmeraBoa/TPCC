CC=gcc
LDFLAGS=-Wall -lfl -ly -lm

bin/tpcc: src/lexer.l src/parser.y obj/abstract-tree.o obj/symbol-table.o obj/sem-check.o obj/translator.o
	bison -d src/parser.y -o src/parser.tab.c
	flex -o src/lex.yy.c src/lexer.l
	$(CC) -o bin/tpcc obj/abstract-tree.o obj/symbol-table.o obj/sem-check.o obj/translator.o src/parser.tab.c src/lex.yy.c $(LDFLAGS)

obj/sem-check.o: src/sem-check.c src/sem-check.h
	gcc -c src/sem-check.c -o obj/sem-check.o 

obj/abstract-tree.o: src/abstract-tree.c src/abstract-tree.h
	gcc -c src/abstract-tree.c -o obj/abstract-tree.o

obj/symbol-table.o: src/symbol-table.c src/symbol-table.h
	gcc -c src/symbol-table.c -o obj/symbol-table.o

obj/translator.o: src/translator.c src/translator.h
	gcc -c src/translator.c -o obj/translator.o

test: _anonymous.asm
	@nasm -f elf64 _anonymous.asm
	@gcc -o _anonymous _anonymous.o -no-pie
	@rm -f _anonymous.o
	@./_anonymous
	@rm -f _anonymous

clean:
	rm -f src/*.tab.c src/*.tab.h src/lex.yy.c
	rm -f obj/*.o
	rm -f bin/tpcc
	rm -f test-report