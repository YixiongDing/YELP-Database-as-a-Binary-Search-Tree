yelp1: yelp.o bst_1.o
	gcc -g -o yelp1 yelp.o bst_1.o

yelp2: yelp.o bst_2.o
	gcc -g -o yelp2 yelp.o bst_2.o

bst_1.o: bst_1.c bst.h
	gcc -c -g -Wall bst_1.c

bst_2.o: bst_2.c bst.h
	gcc -c -g -Wall bst_2.c

yelp.o: yelp.c bst.h
	gcc -c -g -Wall yelp.c
