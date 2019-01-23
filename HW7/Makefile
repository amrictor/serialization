CPPFLAGS=-Wall -Werror -Wextra -Wfatal-errors
CC = g++
assignment=hw7
test=main

$(assignment): $(assignment).o
	g++ $(CPPFLAGS) -c $(assignment).cc
	ar rcs $(assignment).a $(assignment).o
	
full: $(assignment).o $(test).o
	g++ $(CPPFLAGS) -c $(assignment).cc
	ar rcs $(assignment).a $(assignment).o
	g++ $(CPPFLAGS) -o test.o $(test).cc $(assignment).a
	./test.o
tar:
	tar -cv $(MAKEFILE_LIST) $(assignment).cc FSerial.h > $(assignment).tar

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch *.a data testFile tester
