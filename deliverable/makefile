cmake_build=cmake-build-debug

build: build_sample

build_lib: clean
	# get archive
	cp ../$(cmake_build)/lib/*.a lib/
	cp ../src/*.h lib/

build_sample: build_lib
	cp lib/*.h sample/
	cp ../main.cpp sample/
	g++ -std=c++11 sample/main.cpp lib/*.a  -o sample/run.out

clean:
	rm -f lib/*
	rm -rf sample/*
