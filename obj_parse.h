#ifndef __OBJ_PARSE__
#define __OBJ_PARSE__

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct vertex {
	float a;
	float b;
	float c;
};

struct uv {
	float a;
	float b;
};

struct normal {
	float a;
	float b;
	float c;
};

// Using Quads
struct face {
	int vtxes[4];
};

struct obj_model {
	std::vector<vertex> v;
	std::vector<uv>     u;
	std::vector<normal> n;
	std::vector<face>   f;

	obj_model(char *filename);
};

void draw_object(const obj_model &o);

#endif
