NAME := ircserv

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -Iinclude

SRC := src/main.cpp src/Server.cpp src/User.cpp src/UserManager.cpp src/Channel.cpp src/ChannelManager.cpp src/CommandHandler.cpp src/ErrorReplies.cpp \
	src/commands/PassCommand.cpp src/commands/NickCommand.cpp src/commands/UserCommand.cpp \
	src/commands/PingCommand.cpp src/commands/QuitCommand.cpp
OBJ := $(SRC:.cpp=.o)

RM := rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
