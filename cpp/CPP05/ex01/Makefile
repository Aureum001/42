SRCS = src/main.cpp src/Bureaucrat.cpp src/Form.cpp

OBJS = $(SRCS:.cpp=.o)
NAME = ex01
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./inc
CXX = c++
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
