cmake_build=cmake-build-debug

build: clean
	# get archive
	cp ../$(cmake_build)/lib/*.a lib/
	cp ../src/*.h lib/

clean:
	rm -f lib/*.a lib/*.cpp lib/*.h lib/*.out
