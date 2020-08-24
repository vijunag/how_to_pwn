all: got got1

#GOT is resolved before the start of main and
#the GOT table is marked as Read only
#Writing to GOT table results in a SIGSEGV
got: main.c
	gcc -g -O0 -Wl,-z,now main.c -o main

#GOT is resolved during run time and hence not read-only
#Attack can be demonstrated in the below executable
got1: main.c
	gcc -g -O0 main.c -o main1

clean:
	@rm -rf got got1
