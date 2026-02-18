SRCS = src/main.cpp src/Bureaucrat.cpp src/AForm.cpp src/ShrubberyCreationForm.cpp src/RobotomyRequestForm.cpp src/PresidentialPardonForm.cpp

OBJS = $(SRCS:.cpp=.o)
NAME = ex02
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
	$(RM) *_shrubbery

fclean: clean
	$(RM) $(NAME)

re: fclean all