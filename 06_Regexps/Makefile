GENERATES = esub *.o *.txt

all: esub

esub: esub.o 
	cc esub.o -o esub

test:
	echo 'l123091a' | sed -E 's/([123]*(091))/\2\1/' > test1tr.txt
	./esub '([123]*(091))' '\2\1' 'l123091a' > test1pr.txt

	echo 'aba1238' | sed -E 's/([ab]*)/ww/' > test2tr.txt
	./esub '([ab]*)' 'ww' 'abaa1238' > test2pr.txt

	echo 'aaabbbbcc' | sed -E 's/(a*)(b*)(c*)/\3\2\1/' > test3tr.txt
	./esub '(a*)(b*)(c*)' '\3\2\1' 'aaabbbbcc' > test3pr.txt

	cmp test1tr.txt test1pr.txt
	cmp test2tr.txt test2pr.txt
	cmp test3tr.txt test3pr.txt

clean:
	rm -f $(GENERATES)