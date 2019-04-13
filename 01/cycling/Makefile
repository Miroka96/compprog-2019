testcompile: compile test

compile:
	gcc -o program solution.c

test:
	cat 1.in | ./program | diff - 1.out
	cat 2.in | ./program | diff - 2.out
	cat 3.in | ./program | diff - 3.out

clean:
	rm program
