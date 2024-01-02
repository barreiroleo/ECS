MAKEFLAGS += --silent

.PHONY: build clean rebuild run tests
build:
	cmake -S . -B build
	cmake --build build
	ln -sf ./build/compile_commands.json

clean:
	rm build -rf

rebuild: clean build

run: build
	./build/bin/ECS

tests: build
	cd build && make run_all_tests

