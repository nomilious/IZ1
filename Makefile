check:
	sudo ./linters/run.sh

format:
	clang-format -i lib/*.c main.c

build:
	cmake -S . -B build && scan-build cmake --build build

build_fsanitizer:
	cmake -Dfsanitizer=ON -S . -B build && scan-build cmake --build build

test:
	cd build && ./tests/my_test

test_valgrind:
	cd build && valgrind ./tests/my_test

rm_build:
	rm -r build

test_coverage:
	lcov -t "tests/tests_fib" -o coverage.info -c -d fib_lib/ && genhtml -o report coverage.info
