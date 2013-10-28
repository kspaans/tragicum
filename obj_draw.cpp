#include <GL/glfw.h>
#include "obj_parse.h"

void draw_object(const obj_model &o)
{
	std::vector<face>::const_iterator ifce;
	unsigned vidx;

	glBegin(GL_QUADS);
	for (ifce = o.f.begin(); ifce != o.f.end(); ++ifce) {
		//glColor3f(1.0, 0.0, 0.0);
		vidx = ifce->vtxes[0];
		glVertex3f(o.v[vidx].a, o.v[vidx].b, o.v[vidx].c);
		vidx = ifce->vtxes[1];
		glVertex3f(o.v[vidx].a, o.v[vidx].b, o.v[vidx].c);
		vidx = ifce->vtxes[2];
		glVertex3f(o.v[vidx].a, o.v[vidx].b, o.v[vidx].c);
		vidx = ifce->vtxes[3];
		glVertex3f(o.v[vidx].a, o.v[vidx].b, o.v[vidx].c);
	}
	glEnd();
}
