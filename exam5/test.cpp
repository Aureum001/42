#include "bigint.hpp"

void bigint::trim(){
	size_t p = str.find_first_not_of('0');
	if (p == std::string::npos)
		str = "0";
	else
		str = str.substr(p);
}
void bigint::check_digits(){
	if (str.empty())
	{
		str = "0";
		return ;
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			str = "0";
			return ;
		}
	}
}
bigint::bigint() : str("0"){}
bigint::bigint(unsigned int n){
	std::ostringstream oss;
	oss << n;
	str = oss.str();
}
bigint::bigint(const bigint &other) : str(other.str){}
bigint::bigint(const std::string &s) : str(s){
	trim();
	check_digits();
}
bigint &bigint::operator=(const bigint &other){
	if (this != &other)
		str = other.str;
	return (*this);
}
std::string bigint::getStr() const{ return (str);}
bigint bigint::operator+(const bigint &other) const{
	const std::string &A = str;
	const std::string &B = other.str;
	std::string result;
	int i = (int)A.size() - 1;
	int j = (int)B.size() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0 || carry)
	{
		int da = (i >= 0)? A[i] - '0' : 0;
		int db = (j >= 0)? B[j] - '0' : 0;
		int sum = da + db + carry;
		result.push_back(char('0' + (sum % 10)));
		carry = sum / 10;
		i--;
		j--;
	}
	std::reverse(result.begin(), result.end());
	return (bigint(result));
}
bigint &bigint::operator+=(const bigint &other){
	*this = *this + other;
	return (*this);
}
bigint &bigint::operator++(){
	*this += bigint(1);
	return (*this);
}
bigint bigint::operator++(int){
	bigint old = *this;
	++(*this);
	return (old);
}
bigint bigint::operator<<(unsigned int n) const{
	if (n > 0 && str != "0")
		return (bigint(str + std::string(n, '0')));
	return (*this);
}
bigint bigint::operator>>(unsigned int n) const{
	if (n == 0)
		return (*this);
	if (n >= str.size())
		return (bigint("0"));
	return (bigint(str.substr(0, str.size() - n)));
}
bigint &bigint::operator<<=(unsigned int n){
	if (n > 0 && str != "0")
		str.append(n, '0');
	return (*this);
}
bigint &bigint::operator>>=(unsigned int n){
	if (n == 0)
		return (*this);
	if (n >= str.size())
		str = "0";
	else
		str.erase(str.size() - n);
}

static unsigned int to_uint_clamped(const std::string &s)
{
	unsigned long long v = 0;
	const unsigned long long LIM = static_cast<unsigned long long>(~0u);
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
			break ;
		v = v * 10 + (s[i] - '0');
		if (v >= LIM)
			return (static_cast<unsigned int>(LIM));
	}
	return (static_cast<unsigned int>(v));
}

bigint bigint::operator<<(const bigint &other) const{ return (*this << to_uint_clamped(other.str));}
bigint bigint::operator>>(const bigint &other) const{return (*this >> to_uint_clamped(other.str));}
bigint &bigint::operator<<=(const bigint &other){return (*this <<= to_uint_clamped(other.str));}
bigint &bigint::operator>>=(const bigint &other){return (*this >>= to_uint_clamped(other.str));}
bool bigint::operator==(const bigint &other) const{ return (str == other.str);}
bool bigint::operator!=(const bigint &other) const{ return (str != other.str);}
bool bigint::operator<(const bigint &other) const{
	if (str.size() != other.str.size())
		return (str.size() < other.str.size());
	return (str < other.str);
}
bool bigint::operator>(const bigint &other) const{ return (other < *this);}
bool bigint::operator<=(const bigint &other) const{ return !(other < *this);}
bool bigint::operator>=(const bigint &other) const{ return !(*this < other);}
std::ostream &operator<<(std::ostream &os, const bigint &other){
	os << other.getStr();
	return (os);
}