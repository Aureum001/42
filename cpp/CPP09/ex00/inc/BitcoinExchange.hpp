#pragma once

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <time.h>

class BitcoinExchange {
private:
	std::map<std::string, float> _db;

	float        findRate(const std::string &date) const;
	void         parseDatabase();
	void         parseInputFile(const char *file);
	static bool  isValidDate(const std::string &dateStr, struct tm &out);

	BitcoinExchange();

public:
	explicit BitcoinExchange(const char *file);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	class NoDatabaseFile : public std::exception {
		const char *what() const throw();
	};

	class AmountOutOfRange : public std::exception {
		const char *what() const throw();
	};

	class NegativeAmount : public std::exception {
		const char *what() const throw();
	};

	class InvalidDate : public std::exception {
		const char *what() const throw();
	};

	class InvalidFormat : public std::exception {
	public:
		explicit InvalidFormat(const std::string &input);
		~InvalidFormat() throw();
		const char *what() const throw();
	private:
		std::string _msg;
	};

	class WrongHeader : public std::exception {
		const char *what() const throw();
	};

	class NothingToRead : public std::exception {
		const char *what() const throw();
	};
};
