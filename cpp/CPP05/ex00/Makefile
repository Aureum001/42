SRCS = src/main.cpp src/Bureaucrat.cpp

OBJS = $(SRCS:.cpp=.o)
NAME = ex00
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
