check:
	bash linters/run.sh

format:
	clang-format -i lib/*.c main.c

build:
	cmake -Dfsanitizer=OFF -S . -B build && scan-build cmake --build build

build_test:
	cmake -Dfsanitizer=OFF -S . -B build && cmake --build build

build_fsanitizer:
	cmake -Dfsanitizer=ON -S . -B build && scan-build cmake --build build

test:
	sudo ./build/tests/test_fib

test_valgrind:
	sudo valgrind --tool=memcheck --leak-check=yes ./build/tests/test_fib

rm_build:
	rm -r build

test_coverage:
	cd build && lcov -t "tests/test_fib" -o coverage.info -c -d lib/ && genhtml -o report coverage.info

a:	build_fsanitizer test rm_build build test_valgrind rm_build build test test_coverage