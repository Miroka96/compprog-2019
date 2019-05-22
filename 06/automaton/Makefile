testcompilec: compilec testc
testcompilecpp: compilecpp testcpp

compilecpp:
	g++ -o cppprogram automaton.cpp

testcpp:
	cat 1.in | ./cppprogram | diff - 1.out
	cat 2.in | ./cppprogram | diff - 2.out
	cat 3.in | ./cppprogram | diff - 3.out
	cat 4.in | ./cppprogram | diff - 4.out
	cat 5.in | ./cppprogram | diff - 5.out
	cat 6.in | ./cppprogram | diff - 6.out

clean:
	rm cprogram
