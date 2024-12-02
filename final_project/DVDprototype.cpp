#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// 屏幕尺寸
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// DVD标志属性
float logoX = 100.0f, logoY = 100.0f; // 初始位置
float logoRadius = 20.0f;             // 标志半径
float velocityX = 3.0f, velocityY = 2.5f; // 初始速度

int score = 0; // 得分系统

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制DVD标志（圆形）
    glColor3f(0.0f, 0.7f, 1.0f); // 蓝色
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(logoX + cos(angle) * logoRadius, logoY + sin(angle) * logoRadius);
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // 更新标志位置
    logoX += velocityX;
    logoY += velocityY;

    // 边界碰撞检测
    if (logoX - logoRadius <= 0 || logoX + logoRadius >= SCREEN_WIDTH) {
        velocityX = -velocityX; // 水平速度反转
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // 左上角
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // 右下角
    }
    if (logoY - logoRadius <= 0 || logoY + logoRadius >= SCREEN_HEIGHT) {
        velocityY = -velocityY; // 垂直速度反转
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // 左上角
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // 右下角
    }

    glutPostRedisplay(); // 重新绘制屏幕
    glutTimerFunc(16, update, 0); // 每16毫秒更新一次（大约60帧/秒）
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); // 设置正交投影
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("DVD Logo Challenge - 原型");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 黑色背景

    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    glutTimerFunc(16, update, 0); // 启动定时器

    glutMainLoop();
    return 0;
}
