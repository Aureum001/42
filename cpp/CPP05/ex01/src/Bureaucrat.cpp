#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : name_("Unnamed Bureaucrat"), grade_(MIN_GRADE) {
	std::cout << "[Bureaucrat] Default constructor called." << std::endl;
}

Bureaucrat::Bureaucrat(std::string const &name, int grade) : name_(name) {
	std::cout << "[Bureaucrat] Constructor called." << std::endl;
	if (grade < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	if (grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	grade_ = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: name_(other.name_), grade_(other.grade_) {
	std::cout << "[Bureaucrat] Copy constructor called." << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	std::cout << "[Bureaucrat] Copy assignment called." << std::endl;
	if (this != &other)
		grade_ = other.grade_;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "[Bureaucrat] Destructor called." << std::endl;
}

void Bureaucrat::incrementGrade() {
	if (grade_ <= MAX_GRADE)
		throw GradeTooHighException();
	--grade_;
}

void Bureaucrat::decrementGrade() {
	if (grade_ >= MIN_GRADE)
		throw GradeTooLowException();
	++grade_;
}

void Bureaucrat::signForm(Form &form) {
	try {
		form.beSigned(*this);
		std::cout << name_ << " signed " << form.getName() << std::endl;
	} catch (std::exception &e) {
		std::cout << name_ << " couldn't sign " << form.getName()
		          << " because " << e.what() << std::endl;
	}
}

int Bureaucrat::getGrade() const { return grade_; }

std::string Bureaucrat::getName() const { return name_; }

const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade is too low!";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b) {
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}
