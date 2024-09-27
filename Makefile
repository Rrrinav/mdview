cxx := clang++
flags := -Wall -Werror -Wextra -std=c++20

main: main.cpp
	$(cxx) $(flags) main.cpp -o main

clean:
	rm -f main

