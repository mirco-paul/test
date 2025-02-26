all:
	g++ -o test_binary test.cpp && ./test_binary

clean:
	rm -f test_binary
