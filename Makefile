CXX := g++
FLAGS := -Wall -Wextra -Werror -std=c++11
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
NAME := pc_remote

.PHONY: build rebuild debug clean cleanall run

build: $(NAME)

rebuild: cleanall build

debug: FLAGS += -g -fsanitize=address
debug: rebuild

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

cleanall: clean
	$(RM) $(NAME)

run: build
	./$(NAME)
