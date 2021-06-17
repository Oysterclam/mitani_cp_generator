#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif 
/* not SINGLE */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <string.h>
#include "triangle.h"
#include "generate_creases.h"


struct triangulateio *in, *out;


void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'q'){
        printf("dawnaballz\n");
        exit(0);
    }
    if(key == 'n'){
        in = init_in(5);
        out = init_out(in);
        triangulate("pcez", in, out, NULL);
        glutPostRedisplay();
    }
}
void display(){
    printf("dawnaball\n");
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3ub(rand()%255, rand()%255, rand()%255 );
    glColor3ub(0, 0, 0);
    REAL points[10] = {0,0,0,100,100,100,100,0,23,70};
    int edges[16] = {0,1,1,2,2,3,3,0,0,4,1,4,2,4,3,4};
    int indices[4] = {0,1,2,3};
    glBegin(GL_POINTS);
    for(int i=0;i<4;i++){
        glVertex3f(points[2*i],points[2*i+1],0);
    }
    glEnd();
    int done =0;
    for(double i=0;i<=100;i+=0.25){
        for(double j=0;j<=100;j+=0.25){
            points[8] = i;
            points[9] = j;
            REAL *anglez = angles(indices, points, 4, 4);
            int error = fabs(180-kawasakisum(anglez,4,1));
            printf("%d\n",error);
            if(error<0.0001 && done ==0 && i>10 && j>10){

                done++;
            }
            glColor3ub(8*error, 8*error, 8*error);
            glBegin(GL_POINTS);
            glVertex3f(points[8],points[9],0);
            glEnd();
            // for(int i=0;i<8;i++){
            //     glBegin(GL_LINES);
            //     glVertex3f(points[2*edges[2*i]], points[2*edges[2*i]+1], 0);
            //     glVertex3f(points[2*edges[2*i+1]], points[2*edges[2*i+1]+1], 0);
            //     glEnd();
            // }

            // printf("even %f\n",kawasakisum(anglez,4,0));
            // printf("odd %f\n",kawasakisum(anglez,4,1));
            // printf("sum %f\n",kawasakisum(anglez,4,0)+kawasakisum(anglez,4,1));
            printf("error : %g\n", fabs(180-kawasakisum(anglez,4,1)));
        }
    }
                
    glFlush();
}

int main(int argc, char *argv[])
{

    in = init_in(5);
    out = init_out(in);
    triangulate("pcez", in, out, NULL);


    int duh = 2;
    printf("%d\n",~duh);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Delawnay Linsdell");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(5);
    glOrtho(-10.f, 110.f, -10.f, 110.f, 0.f, 1.f );
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMainLoop();
    free_t(in);
    free_t(out);
    return 0;
}
