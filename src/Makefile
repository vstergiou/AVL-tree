
all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

test1: test1.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test2: test2.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test3: test3.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test4: test4.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@
	
test5: test5.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test6: test6.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test7: test7.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test8: test8.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test9: test9.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

test10: test10.cpp AVL.o
	g++ -Wall -g -std=c++11 $^ -o $@

AVL.o: AVL.cpp AVL.hpp
	g++ -g -Wall -std=c++11 AVL.cpp -c
	
clean:
	rm *.o test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 out/* png/* dot/*

run:
	./test1  small.dict.rnd  > out/test1.out
	./test2  small.dict.asc  > out/test2.out
	./test3  small.dict.asc small.dict.des > out/test3.out
	./test4  small.dict.asc > out/test4.out
	./test5  small.dict.rnd > out/test5.out
	./test6  small.dict.rnd > out/test6.out
	./test7  small.dict.rnd tiny.dict > out/test7.out
	./test8  small.dict.rnd tiny.dict > out/test8.out
	./test9  small.dict.rnd small.dict.des > out/test9.out
	./test10 small.dict.rnd small.dict.des > out/test10.out

PNG:
	dot -Tpng dot/test1_dot.dot -o png/test1_tree
	dot -Tpng dot/test2_dot.dot -o png/test2_tree
	dot -Tpng dot/test4_dot.dot -o png/test4_tree
	dot -Tpng dot/test5_dot.dot -o png/test5_tree
	dot -Tpng dot/test6_dot.dot -o png/test6_tree
	dot -Tpng dot/test7_dot.dot -o png/test7_tree
	dot -Tpng dot/test8_dot.dot -o png/test8_tree

