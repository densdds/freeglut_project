#include "freeglut.h"
#include <stdlib.h>
#include <math.h>

static int slices = 16;
static int stacks = 16;

// угол поворота
float angle=0.0;
// направляющий вектор "взгляда"
float lx=0.0f, lz=-1.0f;
// XZ текущая позиция камеры
float x=0.0f, z=5.0f;
//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float deltaAngle = 0.0f;
float deltaMove = 0;




void changeSize(int w, int h) {
        // предотвращение деления на ноль
        if (h == 0)
                h = 1;
        float ratio =  w * 1.0 / h;
        // используем матрицу проекции
        glMatrixMode(GL_PROJECTION);
        // обнуляем матрицу
        glLoadIdentity();
        glViewport(0, 0, w, h);
        // установить корректную перспективу
        gluPerspective(45.0f, ratio, 0.1f, 100.0f);
        // вернуться к матрице проекции
        glMatrixMode(GL_MODELVIEW);
}
//перемещение вдоль вектора направления взгляда
void computePos(float deltaMove)
{
        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
}
//поворот в плоскости (xz)
void computeDir(float deltaAngle)
{
        angle += deltaAngle;
        lx = sin(angle);
        lz = -cos(angle);
}

//просто рисуем объекты
static void display(void)
{


    glPushMatrix();
        glTranslated(-2.4,1.2,-16);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

     glColor3d(0,1,1);
    glPushMatrix();
        glTranslated(0,1.2,-8);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glColor3d(1,0,1);
    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glutSolidTorus(0.2,0.8,slices,stacks);
          glPopMatrix();

        glPushMatrix();
        glTranslated(0,-1.2,-6);
            glutSolidCube(1);
        glPopMatrix();

        glColor3d(0,1,0);
        glPushMatrix();
        glTranslated(-2.4,-1.2,-7);
            glutSolidCylinder(0.5,0.4,slices,stacks);
        glPopMatrix();

        glPushMatrix();
        glTranslated(2.4,-1.2,-6);
            glutSolidIcosahedron();
        glPopMatrix();


        glPushMatrix();
        glTranslated(-2.4,-1.2,-8);
            glutSolidTeapot(1);
        glPopMatrix();



}

//рендеринг сцены , двойная буферизация ,установка камеры
void renderScene(void) {
        if (deltaMove)
                computePos(deltaMove);
        if (deltaAngle)
                computeDir(deltaAngle);
        //очистить буфер цвета и глубины
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // обнулить трансформацию
        glLoadIdentity();
        // установить камеру
        gluLookAt(              x,	1.0f,	  z,
                                x+lx,	1.0f,  z+lz,
                                0.0f,   1.0f,  0.0f		);

        display();

            glutPostRedisplay();
           //вот и буферизация
        glutSwapBuffers();
}
//назначение кнопок.Когда нажата кнопка мы устанавливаем соответствующей переменной ненулевое значение.
//При отпускании клавиши переменная вернется к нулевому значению.
void pressKey(int key, int xx, int yy) {

        switch (key) {
                case GLUT_KEY_LEFT:
                        deltaAngle = -0.01f;
                        break;
                case GLUT_KEY_RIGHT:
                        deltaAngle = 0.01f;
                        break;
                case GLUT_KEY_UP:
                        deltaMove = 0.5f;
                        break;
                case GLUT_KEY_DOWN:
                        deltaMove = -0.5f;
                        break;
        }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
                case GLUT_KEY_LEFT:
                case GLUT_KEY_RIGHT:
                        deltaAngle = 0.0f;
                        break;
                case GLUT_KEY_UP:
                case GLUT_KEY_DOWN:
                        deltaMove = 0;
                        break;
        }
}






const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
/* Program entry point */



int main(int argc, char **argv) {

        // инициализация GLUT и создание окна
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(800,600);
        glutCreateWindow("я пытался");

        // регистрация вызовов
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);
        glutSpecialFunc(pressKey);

        // Новые функции для регистрации
        glutIgnoreKeyRepeat(1);
        glutSpecialUpFunc(releaseKey);

//

        glClearColor(1,1,1,1);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHTING);

            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        // главный цикл
        glutMainLoop();

        return 1;
}
