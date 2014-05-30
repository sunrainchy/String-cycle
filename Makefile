CC = g++
yao.run: yao.cpp
	g++ -o yao.run yao.cpp
clean:
	rm yao.run
