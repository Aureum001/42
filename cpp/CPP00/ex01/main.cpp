#include "header.hpp"


int main() {
	PhoneBook Book;
	int id = 0;
	std::string input;

	std::cout << "Please input...\n";
	while (std::cin >> input) {
		if (input == "ADD") {
			std::string First;
			std::string Last;
			std::string Nick;
			std::string Phone;
			std::string Secret;

			std::cout << "First Name: ";
			std::cin.ignore();
			while (First.empty()) {
				if (!std::getline(std::cin, First))
					return (0);
				if (First.empty()) {
					std::cout << "You can't have an empty first name. Try again...\n";
					std::cout << "Please input your first name: ";
				}
			}
			std::cout << "Last Name: ";
			while (Last.empty()) {
				if (!std::getline(std::cin, Last))
					return (0);
				if (Last.empty()) {
					std::cout << "You can't have an empty last name. Try again...\n";
					std::cout << "Please input your last name: ";
				}
			}
			std::cout << "Nick Name: ";
			while (Nick.empty()) {
				if (!std::getline(std::cin, Nick))
					return (0);
				if (Nick.empty()) {
					std::cout << "You can't have an empty nick name. Try again...\n";
					std::cout << "Please input your nick name: ";
				}
			}
			std::cout << "Phone Number: ";
			while (Phone.empty()) {
				if (!std::getline(std::cin, Phone))
					return (0);
				if (Phone.empty()) {
					std::cout << "You can't have an empty phone number. Try again...\n";
					std::cout << "Please input your phone number: ";
				}
			}
			std::cout << "Darkest Secret: ";
			while (Secret.empty()) {
				if (!std::getline(std::cin, Secret))
					return (0);
				if (Secret.empty()) {
					std::cout << "You can't have an empty darkest secret. Try again...\n";
					std::cout << "Please input your darkest secret: ";
				}
			}
			Book.SetContactId(id, First, Last, Nick, Phone, Secret);
			id = (id + 1) % MaxId;
		} else if (input == "SEARCH") {
			Book.ListPhoneBook();
			std::cout << "\nType id for full informations: ";
			std::string input;
			if (!(std::cin >> input))
				return (0);
			std::stringstream ss(input);
			int id;
			if (!(ss >> id) || !ss.eof() || id < 0 || id >= MaxId || !Book.isContactUsed(id)) {
				std::cout << "Invalid ID\n";
				std::cout << "\nPlease input...\n";
				continue;
			}
			Book.IdPrintContact(id);
		} else if (input == "EXIT") {
			return (0);
		}
		std::cout << "\nPlease input...\n";
	}
	return (0);
}
