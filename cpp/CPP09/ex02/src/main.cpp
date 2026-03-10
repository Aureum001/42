#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: ./PmergeMe <positive integers...>" << std::endl;
		return 1;
	}

	std::vector<int> input;
	input.reserve(static_cast<size_t>(argc - 1));

	for (int i = 1; i < argc; ++i) {
		const std::string arg(argv[i]);
		if (arg.find_first_not_of("0123456789") != std::string::npos) {
			std::cerr << "Error: invalid input: " << arg << std::endl;
			return 1;
		}
		errno = 0;
		const long val = std::strtol(argv[i], NULL, 10);
		if (errno != 0 || val <= 0 || val > INT_MAX) {
			std::cerr << "Error: invalid input: " << arg << std::endl;
			return 1;
		}
		input.push_back(static_cast<int>(val));
	}

	try {
		PmergeMe pm(input);
		pm.sort();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
