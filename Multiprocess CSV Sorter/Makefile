
All: scannerCSVsorter

scannerCSVsorter: scannerCSVsorter.c simpleCSVsorter.c mergesort.c sortKeyFunctions.c
	gcc -ggdb -o scannerCSVsorter scannerCSVsorter.c simpleCSVsorter.c sortKeyFunctions.c mergesort.c -fno-omit-frame-pointer -fsanitize=address
	
clean:
	rm scannerCSVsorter
