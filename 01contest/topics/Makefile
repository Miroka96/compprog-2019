testcompilec: compilec testc
testcompilecpp: compilecpp testcpp

compilec:
	gcc -o cprogram topics.c

compilecpp:
	g++ -o cppprogram topics.cpp

testc:
	cat 1.in | ./cprogram | diff - 1.out
	cat 2.in | ./cprogram | diff - 2.out
	cat 3.in | ./cprogram | diff - 3.out
	cat 4.in | ./cprogram | diff - 4.out

testcpp:
	cat 1.in | ./cppprogram | diff - 1.out
	cat 2.in | ./cppprogram | diff - 2.out
	cat 3.in | ./cppprogram | diff - 3.out
	cat 4.in | ./cppprogram | diff - 4.out

testp:
	cat 1.in | ./topics.py | diff - 1.out
	cat 2.in | ./topics.py | diff - 2.out
	cat 3.in | ./topics.py | diff - 3.out
	cat 4.in | ./topics.py | diff - 4.out

clean:
	rm cprogram
