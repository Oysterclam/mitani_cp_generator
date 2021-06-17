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

int clockwiseof1(const void * a, const void * b){
	// if point b is clockwise from point a (leq 180 degrees)
    int p1 = *(int*)a;
    int p2 = *(int*)b;
    REAL x1 = out->pointlist[2*p1] - out->pointlist[8];
    REAL y1 = out->pointlist[2*p1+1] - out->pointlist[9];
    REAL x2 = out->pointlist[2*p2] - out->pointlist[8];
    REAL y2 = out->pointlist[2*p2+1] - out->pointlist[9];
    if (x1 >= 0 && x2 < 0)
        return 1;
    if (x1 < 0 && x2 >= 0)
        return -1;
    if (x1 == 0 && x2 == 0) {
        if (y1 >= 0 || y2 >= 0)
            return 0;
    }
    int crossprod = cross(x1,y1,x2,y2);
    return crossprod;
}

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

    glBegin(GL_POINTS);
    for(int i=0;i<2*out->numberofpoints;i+=2){
        glVertex3f(out->pointlist[i],out->pointlist[i+1],0);
    }
    glEnd();

    // glPushAttrib(GL_ENABLE_BIT); 
    // glLineStipple(7, 0xAAAA);  
    // glEnable(GL_LINE_STIPPLE);

    for(int i=0;i<2*out->numberofedges;i+=2){
        glBegin(GL_LINES);
        glVertex3f(out->pointlist[2*out->edgelist[i]],out->pointlist[2*out->edgelist[i]+1],0);
        glVertex3f(out->pointlist[2*out->edgelist[i+1]],out->pointlist[2*out->edgelist[i+1]+1],0);
        glEnd();
    }

    int **dawna; 
    
    glPointSize(15);

    dawna = edgelist_to_matrix(out);
    glPointSize(30);
    glColor3ub(255, 0, 0);
    glBegin(GL_POINTS);
    glVertex3f(out->pointlist[8],out->pointlist[9],0);
    int dawna2[4];
    int ind = 0;
    for(int i=0;i<4;i++){
        if(dawna[4][i]==1){
            dawna2[ind]=i;
            ind++;
        }
    }
    glEnd();

    qsort(dawna2, ind, sizeof(int), clockwiseof1);

    for(int i=0;i<ind;i++){
        glBegin(GL_POINTS);
        glColor3ub(255, 0, 0);
        glEnd();
        glVertex3f(out->pointlist[2*dawna2[i]],out->pointlist[2*dawna2[i]+1],0);
        glRasterPos3f(out->pointlist[2*dawna2[i]]+2,out->pointlist[2*dawna2[i]+1],0);
        char gonad[30];
        sprintf(gonad, "%d",i);
        drawstring(out->pointlist[2*dawna2[i]],out->pointlist[2*dawna2[i]+1],0,gonad);
    }
    REAL *anglez = angles(dawna2, out->pointlist, 4, ind);
    for(int i=0;i<ind;i++){
        glRasterPos3f((out->pointlist[2*dawna2[i]]-out->pointlist[8])/7+out->pointlist[8],
                        (out->pointlist[2*dawna2[(i+1)%ind]] - out->pointlist[9])/7+out->pointlist[9],0);
        char gonad[30];
        sprintf(gonad, "%f",anglez[i]);
        drawstring(out->pointlist[2*dawna2[i]],out->pointlist[2*dawna2[i]+1],0,gonad);
    }
    printf("even %f\n",kawasakisum(anglez,ind,0));
    printf("odd %f\n",kawasakisum(anglez,ind,1));
    printf("sum %f\n",kawasakisum(anglez,ind,0)+kawasakisum(anglez,ind,1));

    glEnd();
    glPointSize(15);

    // glPopAttrib();
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
    glPointSize(15);
    glOrtho(-10.f, 110.f, -10.f, 110.f, 0.f, 1.f );
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMainLoop();
    free_t(in);
    free_t(out);
    return 0;
}
