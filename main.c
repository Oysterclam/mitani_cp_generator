#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */

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
	if(key == 'g'){
		in = init_in(14);
		out = init_out(in);
		triangulate("pcez", in, out, NULL);
	}
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	// glColor3ub(rand()%255, rand()%255, rand()%255 );
	glColor3ub(0, 0, 0);

	glBegin(GL_POINTS);
	for(int i=0;i<2*out->numberofpoints;i+=2){
		glVertex3f(out->pointlist[i],out->pointlist[i+1],0);
	}
	glEnd();
	// draw from triangles
	// for(int i=0;i<3*out->numberoftriangles;i+=3){
	// 	glBegin(GL_LINE_LOOP);
	// 	glVertex3f(out->pointlist[2*out->trianglelist[i]],out->pointlist[2*out->trianglelist[i]+1],0);
	// 	glVertex3f(out->pointlist[2*out->trianglelist[i+1]],out->pointlist[2*out->trianglelist[i+1]+1],0);
	// 	glVertex3f(out->pointlist[2*out->trianglelist[i+2]],out->pointlist[2*out->trianglelist[i+2]+1],0);
	// 	glEnd();
	// }

	// glPushAttrib(GL_ENABLE_BIT); 
	// glLineStipple(7, 0xAAAA);  
	// glEnable(GL_LINE_STIPPLE);

	for(int i=0;i<2*out->numberofedges;i+=2){

		glBegin(GL_LINES);
		glVertex3f(out->pointlist[2*out->edgelist[i]],out->pointlist[2*out->edgelist[i]+1],0);
		glVertex3f(out->pointlist[2*out->edgelist[i+1]],out->pointlist[2*out->edgelist[i+1]+1],0);
		glEnd();

	}

	// glPopAttrib();

	glFlush();
}

int main(int argc, char *argv[])
{
	srand(time(0)); 

	in = init_in(14);
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
    glPointSize(10);
    glOrtho(-10.f, 110.f, -10.f, 110.f, 0.f, 1.f );
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

	return 0;
}
