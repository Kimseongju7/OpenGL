#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_FLAT); //마지막 색으로 //glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.5, -0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutCreateWindow("Triangle Example");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}