min_coverage: min_coverage.cpp
	g++ -g -std=c++11 -Wall -o min_coverage min_coverage.cpp

test: min_coverage
	# -------test case-------
	cat testcase.txt
	#
	# -------result output-------
	./min_coverage < testcase.txt

clean:
	rm min_coverage
