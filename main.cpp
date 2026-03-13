#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f( 0.0f,  0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f( 0.5f, -0.5f);
    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Test");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
