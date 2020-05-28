%: %.cpp
	g++ -o $@ $< -std=c++11 -DLOCAL -Wall -Wextra -Wconversion -Wshadow -Wno-sign-conversion -D_GLIBCXX_DEBUG -fno-sanitize-recover=undefined -fsanitize=undefined
