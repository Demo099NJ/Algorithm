longest_path: longest_path.cpp
	g++ -g -std=c++11 -Wall -o longest_path longest_path.cpp

test: longest_path
	# -------test case-------
	cat testcase.txt
	#
	# -------result output-------
	./longest_path < testcase.txt

clean:
	rm longest_path
