#include "str.hpp"

bool strReplace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::vector<std::string> strSplit(std::string& str, std::string delimiter) {
	std::vector<std::string> ret;

	std::string s = str;
	auto pos = s.find(delimiter);

	while (pos != std::string::npos) {
		ret.emplace_back(s.substr(0, s.find(delimiter)));
		s.erase(0, s.find(delimiter) + delimiter.length());
		pos = s.find(delimiter);
	}

	ret.emplace_back(s);

	return ret;
}
