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

struct triangulateio *in, *out;

void keyPressed (unsigned char key, int x, int y) {  
	if(key == 'q'){
		printf("dawnaballz\n");
		exit(0);
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

	glPushAttrib(GL_ENABLE_BIT); 
	glLineStipple(7, 0xAAAA);  
	glEnable(GL_LINE_STIPPLE);

	for(int i=0;i<2*out->numberofedges;i+=2){

		glBegin(GL_LINES);
		glVertex3f(out->pointlist[2*out->edgelist[i]],out->pointlist[2*out->edgelist[i]+1],0);
		glVertex3f(out->pointlist[2*out->edgelist[i+1]],out->pointlist[2*out->edgelist[i+1]+1],0);
		glEnd();

	}

	glPopAttrib();

	glFlush();
}

int main(int argc, char *argv[])
{
	srand(time(0)); 


	in = (struct triangulateio*) malloc(sizeof(struct triangulateio));

	in->numberofpoints = 14;
	in->numberofpointattributes = 0;
	in->numberofholes = 0;
	in->numberofregions = 0;
	in->numberofsegments = 0;
	in->numberoftriangles = 0;


	in->pointlist = (REAL*) malloc(in->numberofpoints*2*sizeof(REAL));
	in->pointattributelist = NULL;
	in->pointmarkerlist = NULL;
	in->segmentmarkerlist = NULL;
	in->segmentlist = NULL;
	in->holelist = NULL;
	in->regionlist = NULL;

	in->pointlist[0] = 0;
	in->pointlist[1] = 0;
	in->pointlist[2] = 0;
	in->pointlist[3] = 100;
	in->pointlist[4] = 100;
	in->pointlist[5] = 100;
	in->pointlist[6] = 100;
	in->pointlist[7] = 0;
	for(int i=8;i<28;i++){
		in->pointlist[i] = rand()%100;
	}


	out = (struct triangulateio*) malloc(sizeof(struct triangulateio));
	out->pointlist = in->pointlist;
	out->pointmarkerlist = NULL;
	out->trianglelist = NULL;
	out->segmentlist = NULL;
	out->segmentmarkerlist = NULL;
	out->edgelist = NULL;
	out->edgemarkerlist = NULL;



	triangulate("pcez", in, out, NULL);



	write_poly(10, 100, 100, "triangle/dawna.poly");
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
