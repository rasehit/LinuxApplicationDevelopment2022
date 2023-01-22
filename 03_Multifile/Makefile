GENERATES = prog prog-* *.a *.so *.o *.txt

all: prog prog-a prog-so 

prog: const.o fun.o prog.o
	cc const.o fun.o prog.o -o prog

prog-a: prog.o static_lib
	cc liboutput_static.a prog.o -o prog-a	

prog-so: out_lib
	cc liboutput.so prog.o -o prog-so

static_lib: fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o 

out_lib: fun.o const.o
	cc -shared fun.o const.o -o liboutput.so

fun.o: outlib.h

test:
	./prog    > test1.txt   2>> test1.txt
	./prog-a  > test1a.txt  2>> test1a.txt
	./prog-so > test1so.txt 2>> test1so.txt
	
	./prog    arg1 > test2.txt   2>> test2.txt
	./prog-a  arg1 > test2a.txt  2>> test2a.txt
	./prog-so arg1 > test2so.txt 2>> test2so.txt
	
	./prog    arg1 arg2 arg3 > test3.txt   2>> test3.txt
	./prog-a  arg1 arg2 arg3 > test3a.txt  2>> test3a.txt
	./prog-so arg1 arg2 arg3 > test3so.txt 2>> test3so.txt
	
	cmp test1.txt test1a.txt
	cmp test1a.txt test1so.txt
	cmp test1so.txt test1.txt

	cmp test2.txt test2a.txt
	cmp test2a.txt test2so.txt
	cmp test2so.txt test2.txt

	cmp test3.txt test3a.txt
	cmp test3a.txt test3so.txt
	cmp test3so.txt test3.txt

clean:
	rm -f $(GENERATES)