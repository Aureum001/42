#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *file)
{
	parseDatabase();
	parseInputFile(file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

float BitcoinExchange::findRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _db.lower_bound(date);
	if (it == _db.end() || it->first != date)
	{
		if (it == _db.begin())
			return _db.begin()->second;
		--it;
	}
	return it->second;
}

void BitcoinExchange::parseDatabase()
{
	std::ifstream dbFile("data.csv");
	if (!dbFile.is_open())
		throw NoDatabaseFile();

	std::string line;
	bool firstLine = true;
	while (std::getline(dbFile, line))
	{
		if (firstLine)
		{
			firstLine = false;
			continue;
		}
		const std::size_t sep = line.find(',');
		if (sep == std::string::npos)
			continue;
		const std::string date = line.substr(0, sep);
		const float rate = static_cast<float>(std::atof(line.c_str() + sep + 1));
		_db[date] = rate;
	}
	if (_db.empty())
		throw NothingToRead();
}

bool BitcoinExchange::isValidDate(const std::string &dateStr, struct tm &out)
{
	if (dateStr.size() != 10)
		return false;
	char *endPtr = strptime(dateStr.c_str(), "%Y-%m-%d", &out);
	if (!endPtr || *endPtr != '\0')
		return false;
	const int year = out.tm_year + 1900;
	const int month = out.tm_mon + 1;
	const int day = out.tm_mday;
	if (month < 1 || month > 12 || day < 1)
		return false;
	int maxDay;
	switch (month)
	{
	case 2:
	{
		const bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		maxDay = leap ? 29 : 28;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
		maxDay = 30;
		break;
	default:
		maxDay = 31;
	}
	return day <= maxDay;
}

void BitcoinExchange::parseInputFile(const char *file)
{
	std::ifstream fs(file);
	if (!fs.is_open())
		throw NoDatabaseFile();

	std::string line;
	bool firstLine = true;

	while (std::getline(fs, line))
	{
		if (firstLine)
		{
			if (line != "date | value")
				throw WrongHeader();
			firstLine = false;
			continue;
		}

		try
		{
			const std::size_t sep = line.find(" | ");
			if (sep == std::string::npos)
				throw InvalidFormat(line);

			const std::string datePart = line.substr(0, sep);
			const std::string amountStr = line.substr(sep + 3);

			if (datePart.empty() || amountStr.empty())
				throw InvalidFormat(line);

			struct tm tm = {};
			if (!isValidDate(datePart, tm))
				throw InvalidFormat(datePart);

			char *pEnd;
			const float amount = std::strtof(amountStr.c_str(), &pEnd);
			if (*pEnd != '\0')
				throw InvalidFormat(line);
			if (amount < 0.0f)
				throw NegativeAmount();
			if (amount > 1000.0f)
				throw AmountOutOfRange();

			const float rate = findRate(datePart);
			std::cout << datePart << " => " << amountStr << " = "
								<< rate * amount << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

BitcoinExchange::InvalidFormat::InvalidFormat(const std::string &input)
		: _msg("Error: bad input => " + input) {}

BitcoinExchange::InvalidFormat::~InvalidFormat() throw() {}

const char *BitcoinExchange::InvalidFormat::what() const throw()
{
	return _msg.c_str();
}

const char *BitcoinExchange::NoDatabaseFile::what() const throw()
{
	return "Error: could not open file.";
}

const char *BitcoinExchange::NothingToRead::what() const throw()
{
	return "Error: empty file.";
}

const char *BitcoinExchange::NegativeAmount::what() const throw()
{
	return "Error: not a positive number.";
}

const char *BitcoinExchange::AmountOutOfRange::what() const throw()
{
	return "Error: too large a number.";
}

const char *BitcoinExchange::WrongHeader::what() const throw()
{
	return "Error: bad input => wrong header.";
}
