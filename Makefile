cxx := clang++
flags := -Wall -ggdb -Werror -Wextra -std=c++20

main: main.cpp
	$(cxx) $(flags) main.cpp -o main

main2: main2.cpp
	$(cxx) $(flags) main2.cpp -o main2

clean:
	rm -f main

