SRCS = main.cpp
SRCS := $(addprefix src/, $(SRCS))

INCLUDES = "./inc"

OBJS = $(SRCS:.cpp=.o)


NAME = ex01
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INCLUDES)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
