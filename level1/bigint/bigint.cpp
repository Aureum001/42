#include "bigint.hpp"

// small helpers implemented here to avoid heavier STL includes
static void reverse_inplace(std::string &s)
{
	if (s.empty())
		return;
	size_t i = 0, j = s.size() - 1;
	while (i < j)
	{
		char t = s[i];
		s[i] = s[j];
		s[j] = t;
		++i;
		--j;
	}
}

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int n)
{
	str = std::to_string(n);
}

bigint::bigint(const std::string &s) : str(s)
{
	trim();
	check_digits();
}

bigint::bigint(const bigint &copy) : str(copy.str) {}

std::string bigint::getStr() const { return str; }

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
		str = other.str;
	return *this;
}

void bigint::trim()
{
	size_t p = str.find_first_not_of('0');
	if (p == std::string::npos)
		str = "0";
	else if (p > 0)
		str = str.substr(p);
}

void bigint::check_digits()
{
	if (str.empty())
	{
		str = "0";
		return;
	}
	for (size_t i = 0; i < str.size(); ++i)
	{
		char c = str[i];
		if (c < '0' || c > '9')
		{
			str = "0";
			return;
		}
	}
}

bigint bigint::operator+(const bigint &other) const
{
	const std::string &A = str;
	const std::string &B = other.str;
	std::string result;
	int i = (int)A.size() - 1;
	int j = (int)B.size() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0 || carry)
	{
		int da = (i >= 0) ? (A[i] - '0') : 0;
		int db = (j >= 0) ? (B[j] - '0') : 0;
		int sum = da + db + carry;
		result.push_back(char('0' + (sum % 10)));
		carry = sum / 10;
		--i;
		--j;
	}
	reverse_inplace(result);
	return bigint(result);
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint old = *this;
	*this = *this + bigint(1);
	return old;
}

bigint bigint::operator<<(unsigned int k) const
{
	if (k == 0 || str == "0")
		return *this;
	return bigint(str + std::string(k, '0'));
}

bigint &bigint::operator<<=(unsigned int k)
{
	if (k > 0 && str != "0")
		str.append(k, '0');
	return *this;
}

bigint bigint::operator>>(unsigned int k) const
{
	if (k == 0)
		return *this;
	if (k >= str.size())
		return bigint("0");
	return bigint(str.substr(0, str.size() - k));
}

bigint &bigint::operator>>=(unsigned int k)
{
	if (k == 0)
		return *this;
	if (k >= str.size())
	{
		str = "0";
	}
	else
		str.erase(str.size() - k);
	return *this;
}

static unsigned int to_uint_clamped(const std::string &s)
{
	unsigned long long v = 0;
	const unsigned long long LIM = static_cast<unsigned long long>(~0u); // UINT_MAX via ~0u
	for (size_t i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if (c < '0' || c > '9')
			break;
		v = v * 10 + (c - '0');
		if (v >= LIM)
			return static_cast<unsigned int>(LIM);
	}
	return static_cast<unsigned int>(v);
}

bigint bigint::operator<<(const bigint &other) const { return (*this) << to_uint_clamped(other.str); }
bigint &bigint::operator<<=(const bigint &other) { return (*this) <<= to_uint_clamped(other.str); }
bigint bigint::operator>>(const bigint &other) const { return (*this) >> to_uint_clamped(other.str); }
bigint &bigint::operator>>=(const bigint &other) { return (*this) >>= to_uint_clamped(other.str); }

bool bigint::operator==(const bigint &other) const { return str == other.str; }
bool bigint::operator!=(const bigint &other) const { return str != other.str; }
bool bigint::operator<(const bigint &other) const
{
	if (str.size() != other.str.size())
		return str.size() < other.str.size();
	return str < other.str;
}
bool bigint::operator>(const bigint &other) const { return other < *this; }
bool bigint::operator<=(const bigint &other) const { return !(other < *this); }
bool bigint::operator>=(const bigint &other) const { return !(*this < other); }

std::ostream &operator<<(std::ostream &os, const bigint &num)
{
	os << num.getStr();
	return os;
}
