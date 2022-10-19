.PHONY: all
all: test-thread

test-thread: test-thread.cpp
	g++ -o test-thread -g test-thread.cpp -lpthread

.PHONY: install
install:
	cp -p test-thread /usr/local/bin/

.PHONY: clean 
clean:
	rm -f test-thread
