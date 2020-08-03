all: library

library: main.cpp ControlMgr.o BookReaderMgr.o Reader.o Book.o 
	g++ -O2 -Wall -I . -o library main.cpp ControlMgr.o BookReaderMgr.o Reader.o Book.o

ControlMgr.o: ControlMgr.cpp
	g++ -O2 -Wall -I . -c ControlMgr.cpp

BookReaderMgr.o: BookReaderMgr.cpp
	g++ -O2 -Wall -I . -c BookReaderMgr.cpp

Reader.o: Reader.cpp
	g++ -O2 -Wall -I . -c Reader.cpp

Book.o: Book.cpp
	g++ -O2 -Wall -I . -c Book.cpp

clean:
	rm -f *.o library 