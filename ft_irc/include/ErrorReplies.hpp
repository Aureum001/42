#ifndef ERRORREPLIES_HPP
#define ERRORREPLIES_HPP

#include <string>

class ErrorReplies
{
public:
	static std::string notRegistered();
	static std::string needMoreParams(const std::string &command);
	static std::string noNicknameGiven();
	static std::string nicknameInUse(const std::string &nick);
	static std::string passwordIncorrect();
};

#endif
