#include <string>
#include <fstream>
#pragma once

namespace zbe {
	namespace file {
		struct input {

			
			static std::string getLine(std::ifstream& stream) {
				std::string line;
				std::getline(stream, line);
				return line;
			}

			static int getInt(std::string& data, char deliminator) {
				if (data.empty()) {
					throw std::invalid_argument("Expected number data, got empty");
				}
				std::string substr = data.substr(0, data.find(deliminator));
				data = data.substr(data.find(deliminator), data.length());

				return stoul(substr);

			}

			static float getFloat(std::string& data, char deliminator) {
				if (data.empty()) {
					throw std::invalid_argument("Expected number data, got empty");
				}
			}
			
		};
	}
}
