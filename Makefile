# -O2 

build:
	clang -o build-c tailcalls.c
	clang++ -o build-cpp tailcalls.c
	clang -O2 -o build-c-opt tailcalls.c
	clang++ -O2 -o build-cpp-opt tailcalls.c
	gcc -O2 -o gcc-build-c-opt tailcalls.c
	g++ -O2 -o gcc-build-cpp-opt tailcalls.c

	# This should not build because they will blow out the stack
	gcc -o gcc-build-c tailcalls.c
	g++ -o gcc-cpp tailcalls.c

