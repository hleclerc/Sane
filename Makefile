CMD = nsmake run -O3 -g3 --cpp-flag -march=native --cpp-flag -Wall --cpp-flag -std=c++17 -o sane src/sane.cpp

all: cmp # test #

cmp: # test
	${CMD} tests/basic.met
	
# prof:
# 	rm -f callgrind.out.* 2> /dev/null
# 	nsmake exe -O3 -g3 --cpp-flag -march=native --cpp-flag -Wall -o crumf_interpreter interpreter/crumf_interpreter.cpp
# 	valgrind --tool=callgrind ./crumf_interpreter src/sane.met test/basic.met
# 	kcachegrind callgrind.out.* &

test:
	nsmake gtest -g3 --cpp-flag -march=native --cpp-flag -Wall tests/test_Variable.cpp

.PHONY: test cmp
