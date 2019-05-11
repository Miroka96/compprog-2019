testcompilec: compilec testc
testcompilecpp: compilecpp testcpp

compilec:
	gcc -o cprogram triangles.c

compilecpp:
	g++ -o cppprogram triangles.cpp

testc:
	cat 1.in | ./cprogram | diff - 1.out
	cat 2.in | ./cprogram | diff - 2.out
	cat 3.in | ./cprogram | diff - 3.out

testcpp:
	cat 1.in | ./cppprogram | diff - 1.out
	cat 2.in | ./cppprogram | diff - 2.out
	cat 3.in | ./cppprogram | diff - 3.out

testp:
	cat 1.in | ./solution.py | diff - 1.out
	cat 2.in | ./solution.py | diff - 2.out
	cat 3.in | ./solution.py | diff - 3.out

clean:
	rm cprogram
