dict_1: dict_1.o 
	gcc -o dict_1 dict_1.o 

dict_1.o: dict_1.c bst_1.c bst_1.h
	gcc -c -Wall dict_1.c


dict_2: dict_2.o
	gcc -o dict_1 dict_2.o 
	   
dict_2.o: dict_2.c bst_1.c bst_1.h
	gcc -c -Wall dict_2.c


clean:
	rm -f *.o