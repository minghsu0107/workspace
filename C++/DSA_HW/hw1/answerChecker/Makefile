PROG_LIST = prog1 prog2 generator
CASE_LIST = $(shell seq 1 5)
RESULT_LIST := $(foreach X,$(CASE_LIST),result$X.txt)
all: $(RESULT_LIST)
	ls -l $^
input1.txt: generator Makefile
	./generator 8 3 2 19 1337 > input1.txt
input2.txt: generator Makefile
	./generator 20 5 5 49 1337 > input2.txt
input3.txt: generator Makefile
	./generator 600 300 149 2147483647 1337 > input3.txt
input4.txt: generator Makefile
	./generator 10000 5000 2499 2147483647 1337 > input4.txt
input5.txt: generator Makefile
	./generator 200000 100000 49999 2147483647 1337 > input5.txt
CXX = g++
CXXFLAGS = -std=c++11 -O2
$(PROG_LIST): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# result1.txt: testing result of input1.txt between prog1 and prog2
# $*: matches % in the pattern
$(RESULT_LIST): result%.txt: input%.txt prog1 prog2
	echo "testcase: $<" > $@
	echo "prog1:" >> $@
	./prog1 < $< > output$*.prog1.txt
	cat output$*.prog1.txt >> $@
	echo "prog2:" >> $@
	./prog2 < $< > output$*.prog2.txt
	cat output$*.prog2.txt >> $@
	diff -y output$*.prog1.txt output$*.prog2.txt || echo "wrong answer" >> $@
	cat $@
# @: do not show the command to stdout
clean:
	@rm -f input*.txt output*.txt tmp*.txt $(PROG_LIST) $(RESULT_LIST)
### how to use ###

# example:
# make result1.txt
# make clean
