all:
	make clean
	mkdir -p build && cd build && cmake .. && make

verbose:
	make clean
	mkdir -p build && cd build && cmake .. && make VERBOSE=1;

example:
	make clean
	mkdir -p build && cd build && cmake .. && make && ./example

clean:
	@rm -rf build/*
