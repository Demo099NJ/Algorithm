hello: hello.cpp
	g++ -g -Wall -std=c++11 -o hello hello.cpp

test: hello
	#-----------------------------------------
	./hello < ../testcase.txt

clean:
	rm -f hello
