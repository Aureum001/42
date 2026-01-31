#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(const std::string& content, const std::string& s1, const std::string& s2) {
	if (s1.empty())
		return content;
	std::string result;
	size_t pos = 0;
	size_t found;

	while ((found = content.find(s1, pos)) != std::string::npos) {
		result.append(content, pos, found - pos);
		result.append(s2);
		pos = found + s1.length();
	}
	result.append(content, pos, content.length() - pos);
	return result;
}

int main(int argc, char **argv) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
		return 1;
	}

	std::string content;
	std::string line;
	while (std::getline(infile, line)) {
		content += line;
		if (!infile.eof())
			content += '\n';
	}
	infile.close();

	std::string result = replaceAll(content, argv[2], argv[3]);

	std::string outfileName = std::string(argv[1]) + ".replace";
	std::ofstream outfile(outfileName.c_str());
	if (!outfile.is_open()) {
		std::cerr << "Error: Cannot create file " << outfileName << std::endl;
		return 1;
	}

	outfile << result;
	outfile.close();

	return 0;
}