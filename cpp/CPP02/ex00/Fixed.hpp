#ifndef EX00_FIXED_HPP
#define EX00_FIXED_HPP

class Fixed {
private:
	int _value;
	static const int _fractionalBits = 8;

public:
	Fixed();
	Fixed(const Fixed& other);
	Fixed& operator=(const Fixed& other);
	~Fixed();
	
	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif
