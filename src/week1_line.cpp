#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
        glLineWidth(5.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutCreateWindow("Line Example");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}