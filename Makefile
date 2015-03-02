# this rule invokes the rule below
#
all: tweets

hashtable.o:  hashtable.c hashtable.h
	clang -c hashtable.c -g

tweets:  tweets.c hashtable.o
	clang -o tweets tweets.c hashtable.o -g
	
clean: 
	rm -rf *.o
	
clobber: clean
	rm -rf tweets
	rm -rf *.out