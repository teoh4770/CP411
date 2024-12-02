#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ��Ļ�ߴ�
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// DVD��־����
float logoX = 100.0f, logoY = 100.0f; // ��ʼλ��
float logoRadius = 20.0f;             // ��־�뾶
float velocityX = 3.0f, velocityY = 2.5f; // ��ʼ�ٶ�

int score = 0; // �÷�ϵͳ

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ����DVD��־��Բ�Σ�
    glColor3f(0.0f, 0.7f, 1.0f); // ��ɫ
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(logoX + cos(angle) * logoRadius, logoY + sin(angle) * logoRadius);
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // ���±�־λ��
    logoX += velocityX;
    logoY += velocityY;

    // �߽���ײ���
    if (logoX - logoRadius <= 0 || logoX + logoRadius >= SCREEN_WIDTH) {
        velocityX = -velocityX; // ˮƽ�ٶȷ�ת
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // ���Ͻ�
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // ���½�
    }
    if (logoY - logoRadius <= 0 || logoY + logoRadius >= SCREEN_HEIGHT) {
        velocityY = -velocityY; // ��ֱ�ٶȷ�ת
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // ���Ͻ�
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // ���½�
    }

    glutPostRedisplay(); // ���»�����Ļ
    glutTimerFunc(16, update, 0); // ÿ16�������һ�Σ���Լ60֡/�룩
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); // ��������ͶӰ
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("DVD Logo Challenge - ԭ��");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ��ɫ����

    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    glutTimerFunc(16, update, 0); // ������ʱ��

    glutMainLoop();
    return 0;
}
