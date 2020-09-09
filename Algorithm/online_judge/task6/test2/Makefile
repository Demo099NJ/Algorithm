max_impact: max_impact.cpp
	g++ -g -std=c++11 -Wall -o max_impact max_impact.cpp

test: max_impact
	# -------test case-------
	cat testcase.txt
	#
	# -------result output-------
	./max_impact < testcase.txt

clean:
	rm max_impact
