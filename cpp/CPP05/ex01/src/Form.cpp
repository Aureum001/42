#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: name_("Unnamed Form"), isSigned_(false), signGrade_(MIN_GRADE), execGrade_(MIN_GRADE) {
	std::cout << "[Form] Default constructor called." << std::endl;
}

Form::Form(const std::string &name, int signGrade, int execGrade)
	: name_(name), isSigned_(false), signGrade_(signGrade), execGrade_(execGrade) {
	std::cout << "[Form] Constructor called." << std::endl;
	if (signGrade < 1 || execGrade < 1)
		throw Form::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form &other)
	: name_(other.name_), isSigned_(other.isSigned_),
	  signGrade_(other.signGrade_), execGrade_(other.execGrade_) {
	std::cout << "[Form] Copy constructor called." << std::endl;
}

Form &Form::operator=(const Form &other) {
	std::cout << "[Form] Copy assignment called." << std::endl;
	if (this != &other)
		isSigned_ = other.isSigned_;
	return *this;
}

Form::~Form() {
	std::cout << "[Form] Destructor called." << std::endl;
}

std::string Form::getName() const { return name_; }

bool Form::getSigned() const { return isSigned_; }

int Form::getSignGrade() const { return signGrade_; }

int Form::getExecGrade() const { return execGrade_; }

void Form::beSigned(const Bureaucrat &signer) {
	if (signer.getGrade() > signGrade_)
		throw Form::GradeTooLowException();
	isSigned_ = true;
}

const char *Form::GradeTooHighException::what() const throw() {
	return "form grade is too high!";
}

const char *Form::GradeTooLowException::what() const throw() {
	return "form grade is too low!";
}

std::ostream &operator<<(std::ostream &os, const Form &f) {
	os << "Form \"" << f.getName() << "\"" 
	   << " | signed: " << (f.getSigned() ? "yes" : "no")
	   << " | sign grade: " << f.getSignGrade()
	   << " | exec grade: " << f.getExecGrade();
	return os;
}
