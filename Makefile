
all:
	cmake -B build
	cmake --build build

test:
	cmake -B build -DTESTING=ON
	cmake --build build

clean:
	rm -rf build

fclean: clean
	rm -rf bin
