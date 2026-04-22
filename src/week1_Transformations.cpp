#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void MyDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);
    glMatrixMode(GL_MODELVIEW);

    // Red square
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glutSolidCube(0.3);

    // green square
    glLoadIdentity();
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(45, 0, 0, 1);
    glTranslatef(0.6, 0.0, 0.0);
    glutSolidCube(0.3);

    // blue square
    glColor3f(0.0, 0.0, 1.0);
    glLoadIdentity();
    glTranslatef(0.6, 0.0, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glutSolidCube(0.3);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutCreateWindow("OpenGL Simple Drawing");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 0);

    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}