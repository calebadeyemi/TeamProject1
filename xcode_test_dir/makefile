cmake_build_dir=cmake-build-debug

build: clean
	cp ../src/*.cpp ../src/*.h .
	cp ../main.cpp .
	g++ -std=c++17 *.cpp

clean:
	rm -f *.cpp *.h *.out *.a 2>/dev/null
