#pragma once
#include <fstream>

namespace nexus::util {
[[nodiscard]] inline std::string read_file(const std::string& filename) {
	std::string buffer;
	std::ifstream file(filename);
	file.seekg(std::ios::end);
	buffer.resize(static_cast<unsigned int>(file.tellg()));
	file.seekg(std::ios::beg);
	file.read(buffer.data(), buffer.size());
	file.close();
	return buffer;
}

void write_file(const std::string& filename, std::string&& buffer) {
	std::ofstream file(filename);
	file.write(buffer.data(), buffer.size());
	file.close();
}
}  // namespace util