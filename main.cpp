#include <GL/glfw.h>
#include <math.h>
#include "obj_parse.h"

#define WIDTH  640
#define HEIGHT 480

void draw_cube() {
  glBegin(GL_QUADS);
  // Top
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-0.5, 0.5, -0.5); // 0
  glVertex3f(0.5, 0.5, -0.5); // 1
  glVertex3f(0.5, 0.5, 0.5); // 2
  glVertex3f(-0.5, 0.5, 0.5); // 3

  // Front
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, 0.5, 0.5);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(0.5, -0.5, 0.5); // 5
  glVertex3f(-0.5, -0.5, 0.5); // 4

#if 0
  // Bottom
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, 0.5);
  glVertex3f(0.5, -0.5, 0.5);
  glVertex3f(0.5, -0.5, -0.5); // 7
  glVertex3f(-0.5, -0.5, -0.5); // 6

  // Back
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5); // 8
  glVertex3f(0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, -0.5, -0.5); // 9

  // Left
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, 0.5);
  glVertex3f(-0.5, -0.5, 0.5);
  glVertex3f(-0.5, -0.5, -0.5);

  // Right
  glColor3f(0.0, 1.0, 1.0);
  glVertex3f(0.5, 0.5, -0.5); // 1
  glVertex3f(0.5, 0.5, 0.5); // 2
  glVertex3f(0.5, -0.5, 0.5);
  glVertex3f(0.5, -0.5, -0.5);
#endif

  glEnd();
}

int main(int argc, char** argv) {
  glfwInit();
  glfwOpenWindow(WIDTH, HEIGHT, 8, 8, 8, 8, 32, 0, GLFW_WINDOW);

  // Setup OpenGL stuff
  glEnable(GL_DEPTH_TEST);

  glClearColor(0, 0, 0, 0);

  glViewport(0, 0, WIDTH, HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, (float)WIDTH/(float)HEIGHT, 0.1, 10.0);
  glMatrixMode(GL_MODELVIEW);

  if (argv[1]) {
    obj_model m(argv[1]);

    std::cout << "size is " << m.v.size() << std::endl;
    std::cout << "Vertex is " << m.v[0].a << "," << m.v[0].b << "," << m.v[0].c
      << std::endl;
    std::cout << "Vertex2is " << m.v[1].a << "," << m.v[1].b << "," << m.v[1].c
      << std::endl;
  }

  int running = 1;
  int jumping = 0;
  float rotZ = 0;
  float rotY = 0;
  float rotX = 0;
  float posnZ = 2;
  float posnY =  0;
  float posnX =  0;
  float velo = 0;

  const float GRAVITY = -0.005;
  const float LOOK_X_TOP = +M_PI/3.;
  const float LOOK_X_BOT = -M_PI/3.;

  float lookX = 0; /* in radians */
  float lookY = 0; /* aka THETA, in radians */

  while(running) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* Look around */
    if (glfwGetKey('F')) lookX -= 0.02;
    if (glfwGetKey('R')) lookX += 0.02;
    if (lookX >= LOOK_X_TOP) lookX = LOOK_X_TOP;
    if (lookX <= LOOK_X_BOT) lookX = LOOK_X_BOT;
    glRotatef(-lookX * (180./M_PI), 1, 0, 0);
    if (glfwGetKey('H')) lookY -= 0.02;
    if (glfwGetKey('G')) lookY += 0.02;
    glRotatef(-lookY * (180./M_PI), 0, 1, 0);

    // Setup camera transformation
    if (glfwGetKey(GLFW_KEY_UP)) {
      posnX -= 0.01 * sin(lookY);
      posnZ -= 0.01 * cos(lookY);
    }
    if (glfwGetKey(GLFW_KEY_DOWN)) {
      posnX += 0.01 * sin(lookY);
      posnZ += 0.01 * cos(lookY);
    }
    if (glfwGetKey(GLFW_KEY_LEFT)) {
      posnX -= 0.01 * cos(lookY);
      posnZ += 0.01 * sin(lookY);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT)) {
      posnX += 0.01 * cos(lookY);
      posnZ -= 0.01 * sin(lookY);
    }
    if (glfwGetKey(GLFW_KEY_SPACE)) { velo = 0.1; jumping = 1; }
    if (jumping) {
      posnY += velo;
      if (posnY >= 0) {
        velo += GRAVITY;
      } else {
        jumping = 0;
        posnY = 0;
      }
    }
    glTranslatef(-posnX, -posnY, -posnZ);

    // Setup model transformation
    if (glfwGetKey('Q')) rotZ += 0.2;
    if (glfwGetKey('E')) rotZ -= 0.2;
    if (glfwGetKey('A')) rotY += 0.2;
    if (glfwGetKey('D')) rotY -= 0.2;
    if (glfwGetKey('W')) rotX += 0.2;
    if (glfwGetKey('S')) rotX -= 0.2;
    glRotatef(rotZ, 0, 0, 1);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotX, 1, 0, 0);

    // Draw!
    draw_cube();

    glfwSwapBuffers();
    running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
  }
}
