testcompile: compile test
testcompilecpp: compilecpp testcpp

test: testcpp
compile: compilecpp

compilecpp:
	g++ -o cppprogram editor.cpp

testcpp:
	cat 1.in | ./cppprogram | diff - 1.out
	cat 2.in | ./cppprogram | diff - 2.out
	cat 3.in | ./cppprogram | diff - 3.out
	cat 4.in | ./cppprogram | diff - 4.out
	cat 5.in | ./cppprogram | diff - 5.out
	cat 6.in | ./cppprogram | diff - 6.out
	cat 7.in | ./cppprogram | diff - 7.out
	cat 8.in | ./cppprogram | diff - 8.out
	cat 9.in | ./cppprogram | diff - 9.out
	cat 10.in | ./cppprogram | diff - 10.out

t1:
	cat 1.in | ./cppprogram

t2:
	cat 2.in | ./cppprogram

t3:
	cat 3.in | ./cppprogram

t4:
	cat 4.in | ./cppprogram

t5:
	cat 5.in | ./cppprogram

t6:
	cat 6.in | ./cppprogram

t7:
	cat 7.in | ./cppprogram

t8:
	cat 8.in | ./cppprogram

t9:
	cat 9.in | ./cppprogram

t10:
	cat 10.in | ./cppprogram

testp:
	cat 1.in | ./editor.py | diff - 1.out
	cat 2.in | ./editor.py | diff - 2.out
	cat 3.in | ./editor.py | diff - 3.out
	cat 4.in | ./editor.py | diff - 4.out
	cat 5.in | ./editor.py | diff - 5.out
	cat 6.in | ./editor.py | diff - 6.out
	cat 7.in | ./editor.py | diff - 7.out
	cat 8.in | ./editor.py | diff - 8.out
	cat 9.in | ./editor.py | diff - 9.out
	cat 10.in | ./editor.py | diff - 10.out

clean:
	rm cppprogram
