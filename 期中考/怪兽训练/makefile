test: 1007hza.o 1007hzl.o test.cpp
	g++-4.8 --std=c++11 -g -o test 1007hza.o 1007hzl.o test.cpp

1007hza.o: 1007hza.cpp
	g++-4.8 --std=c++11 -g -c 1007hza.cpp
1007hzl.o: 1007hzl.cpp
	g++-4.8 --std=c++11 -g -c 1007hzl.cpp

clean: 1007hza.o 1007hzl.o test
	rm -f 1007hza.o 1007hzl.o test