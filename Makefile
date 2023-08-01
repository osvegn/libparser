
all:
	cmake -B build
	cmake --build build

run_tests:
	cmake -B build -DTESTING=ON
	cmake --build build
	./bin/test_parser

clean:
	rm -rf build

fclean: clean
	rm -rf bin
