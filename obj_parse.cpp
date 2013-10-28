#include <fstream>
#include "obj_parse.h"

obj_model::obj_model(char *filename) {
	std::ifstream inf(filename);
	std::string token;

	if (!inf) {
		//std::cout << "Couldn't open file \"" << filename << "\""
		//	<< std::endl;
		return;
	} else {
		//std::cout << "Opened file \"" << filename  << "\"" <<
		//	std::endl;
	}

	// TODO Boost::coroutine for parsing?
	while (inf) {
		inf >> token;
		//std::cout << "Found a token '" << token << "'" << std::endl;

		if (0 == token.compare("#")) {
			std::getline(inf, token);
			continue;
		}

		if (0 == token.compare("v")) {
			std::string v2, v3;
			inf >> token;
			inf >> v2;
			inf >> v3;
			vertex v = {
				std::stof(token), std::stof(v2), std::stof(v3)
			};
			obj_model::v.push_back(v);
		}

		if (0 == token.compare("vt")) {
			std::string v2;
			inf >> token;
			inf >> v2;
			uv u = {
				std::stof(token), std::stof(v2)
			};
			obj_model::u.push_back(u);
		}

		if (0 == token.compare("vn")) {
			std::string v2, v3;
			inf >> token;
			inf >> v2;
			inf >> v3;
			normal n = {
				std::stof(token), std::stof(v2), std::stof(v3)
			};
			obj_model::n.push_back(n);
		}
	}
}
