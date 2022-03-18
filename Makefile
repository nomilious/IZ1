check:
	bash linters/run.sh

format:
	clang-format -i lib/*.c main.c

build:
	cmake -S . -B build && scan-build cmake --build build

build_test:
	cmake -S . -B build && cmake --build build

build_fsanitizer:
	cmake -Dfsanitizer=ON -S . -B build && scan-build cmake --build build

test:
	sudo ./build/tests/my_test

test_valgrind:
	sudo valgrind ./build/tests/my_test

rm_build:
	rm -r build

test_coverage:
	lcov -t "tests/my_test" -o coverage.info -c -d lib/ && genhtml -o report coverage.info
