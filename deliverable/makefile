cmake_build=cmake-build-debug

build: clean
	# get archive
	cp ../$(cmake_build)/lib/*.a .
	cp ../src/*.h .
	cp ../main.cpp .
	g++ -std=c++17 main.cpp *.a

clean:
	rm -f *.a *.cpp *.h
