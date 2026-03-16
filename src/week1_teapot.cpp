#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

void reshape(int w, int h){
    glLoadIdentity();
    glViewport(0, 0, w, h); // 어떤 기준으로 그림을 그릴 지
    gluOrtho2D(0.0, 100, 0.0, 100); // 어떤 부분을 보여줄 지 보다 눈금을 그리는 게 더 정확한 듯. 눈금 이상의 그림을 그릴려고 하면 짤려 보이는 거고
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidTeapot(0.5);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTeapot(0.5);

    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutCreateWindow("teapot example");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}