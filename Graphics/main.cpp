#include <GLUT/GLUT.h>
#include <math.h>

GLfloat x= -0.9, y=-0.4;//start point of a ball
GLfloat dx = 0.0;//dalta of x
GLfloat dy = 0.0;//delta of y
GLfloat x_flag = 1;//whether x+dx is positive or not
GLfloat y_flag = 1;//whether y+dy is positive or not

void DrawCircle(float cx, float cy, float r)
{
    float x1, y1, x2, y2;
    float angle;
    double radius = r;
    
    x1 = cx, y1 = cy;
    glColor3f(1.0, 1.0, 0.6);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    
    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle)*radius;
        y2 = y1 + cos(angle)*radius;
        glVertex2f(x2, y2);
    }
    
    glEnd();
}



void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    DrawCircle(x + dx, y + dy, 0.1);//set random position of a ball
    
    glEnd();
    glutSwapBuffers();
}

void MyTimer(int Value) {
    //checking x+dx range
    if(x+dx < -0.9)
        x_flag = 1;
    else if(x+dx > 0.9)
        x_flag = 0;
    (x_flag) ? dx += 0.01 : dx -= 0.01;//change x direction
    
    //checking y+dy range
    if(y+dy < -0.9)
        y_flag = 1;
    else if(y+dy > 0.9)
        y_flag = 0;
    (y_flag) ? dy += 0.01 : dy -= 0.01;//change of y direction
    
    glutPostRedisplay();
    glutTimerFunc(20, MyTimer, 1);//set 20 millisec time for timer
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 0.5, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    glutDisplayFunc(MyDisplay);
    glutTimerFunc(20, MyTimer, 1);
    glutMainLoop();
    return 0;
}
