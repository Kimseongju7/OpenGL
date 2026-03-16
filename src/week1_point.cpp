#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif
#include<math.h>
#include<stdio.h>
#define PI 3.14

void display(void){
    GLfloat size[2];
    GLfloat angle;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glGetFloatv(GL_POINT_SIZE_RANGE, size);
    glPointSize(size[0]); // size[1] : 최대값, (size[1] - size[0] / 2) + size[0] : 중간값
    glBegin(GL_POINTS);
    int cnt = 0;
    for(angle = 0.0; angle <= 2.0 * PI; angle += PI / 30.0) {
        glVertex3f(0.5 * cos(angle), 0.5 * sin(angle), 0.0); printf("%f %d\n", angle, cnt++);}
    glEnd();
    //   각도를 0 ~ 2π까지 π/30씩 증가 (총 60개 점)
    //   각 점의 좌표를 삼각함수로 계산 → 반지름 0.5짜리 원
    // angle이 theta임.

    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutCreateWindow("Point Example");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}