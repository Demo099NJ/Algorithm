anagram: anagram.cpp
	g++ -g -std=c++11 -Wall -o anagram anagram.cpp

test:
	# -------test case-------
	cat testcase.txt
	#
	# -------result output-------
	./anagram < testcase.txt
	#
	# -------expected output-------
	cat expected.txt

clean:
	rm anagram
