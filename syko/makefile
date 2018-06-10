SRC=mem_abs.c \
instr.c \
interrupt.c \
interpreter.c \
counter.c \
main.c

syko.exe: $(SRC)
	gcc -O0 -c mem_abs.c -o mem_abs.o
	gcc -O0 -c instr.c -o instr.o
	gcc -O0 -c interrupt.c -o interrupt.o
	gcc -O0 -c interpreter.c -o interpreter.o
	gcc -O0 -c counter.c -o counter.o
	gcc -O0 -c main.c -o main.o
	gcc mem_abs.o instr.o interrupt.o interpreter.o counter.o main.o -o syko.exe

clean:
	rm -f mem_abs.o
	rm -f instr.o
	rm -f interrupt.o
	rm -f interpreter.o
	rm -f counter.o
	rm -f main.o
	rm -f syko.exe

