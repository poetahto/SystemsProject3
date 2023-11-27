all:
	g++ -std=c++11 -o disassem -g3 -O0 $(wildcard *.cpp)

clean:
	rm disassem

