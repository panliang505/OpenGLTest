#include "GL/glut.h"

void init(void)
{
    glClearColor(0.9,0.9,0.9, 0.0);   // set display-window color towhite

    glMatrixMode(GL_PROJECTION);        // set projection parameters
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment()
{
    glClear(GL_COLOR_BUFFER_BIT);   // clear display window
        
    glColor3f(1.0, 0.4, 0.2);       // set line segment color to green
    glBegin(GL_LINES);
    //glVertex2i(95, 80);
    glVertex2i(0, 150);             // specify line-segment geometry
    glVertex2i(200, 0);
    glVertex2i(50, 150);
    glVertex2i(100, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(50, 50);
    glVertex2i(100, 100);
    glVertex2i(50, 100);
    glVertex2i(0, 50);
    glVertex2i(50, 50);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(120, 50);
    glVertex2i(170, 100);
    glVertex2i(120, 100);
    glVertex2i(70, 50);
    //glVertex2i(100, 50);
    glEnd();

   

    glFlush();                      // process all opengl routines as quickly as possible
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // set display mode
    glutInitWindowPosition(50, 100);                // set top-left display-window position
    glutInitWindowSize(400, 300);                   // set display-window width and height
    glutCreateWindow("An Example OpenGL Program");  // create display window

    init();                                         // execute initialization procedure
    glutDisplayFunc(lineSegment);                   // send graphics to display window
    glutMainLoop();                                 // display everything and wait
}