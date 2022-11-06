#define FREEGLUT_STATIC
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <windows.h>
#define MAX_CHAR 128

void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
//greetings
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (;*str != '\0';++str) {
		glCallList(lists + *str);
	}
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
void text() {
	selectFont(60, ANSI_CHARSET, "Blackadder ITC");
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(150, 315);  //Position of text start
	drawString(" Happy new year!");
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(152, 315);
	drawString(" Happy new year!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(370, 160);
	drawString("Peace and Joy");
}
//draw balloon strings
GLfloat ctrlpoints1[4][3] = { // 4 points to define a cubic Bezier curve
{ 100.0, 230.0, 0.0 }, // Point 0
{ 80.0, 260.0, 0.0 }, // Point 1
{ 120.0, 260.0, 0.0 }, // Point 2
{ 100.0, 290.0, 0.0 } }; // Point 3

GLfloat ctrlpoints2[4][3] = {
{ 500.0, 230.0, 0.0 },
{ 480.0, 260.0, 0.0 },
{ 520.0, 260.0, 0.0 },
{ 500.0, 290.0, 0.0 } };

void myinit1(void) {
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints1[0][0]);
	glEnable(GL_MAP1_VERTEX_3); // Enable the evaluator.
	glShadeModel(GL_FLAT);
}
void myinit2(void) {
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints2[0][0]);
	glEnable(GL_MAP1_VERTEX_3); 
	glShadeModel(GL_FLAT);
}
void balloonstring1() {
	//draw - beisaierquxian
	//Plot Bezier Curve between Point 0 and Point 3
	glLineWidth(3);  //Specify thickness
	glColor3f(0.69, 0.09, 0.12);
	int number = 50; 
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= number; i++) {
		/* glEvalCoord1f evaluates the one-dimensional maps that are enabled.
		 void glEvalCoord1f(GLfloat u);
		 u specifies a value that is the domain coordinate u to the basis function defined in a previous
		glMap1 function. */
		glEvalCoord1f((GLfloat)i / number);
	}
	glEnd();
	glPointSize(1.0);
	glColor3f(1, 0.75, 0.8);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&ctrlpoints1[i][0]); // Draw each control point
	}
	glEnd();
}
void balloonstring2() {
	glLineWidth(3);
	glColor3f(0.69, 0.09, 0.12);
	glBegin(GL_LINE_STRIP);
	int number = 50;
	for (int i = 0; i <= number; i++) {
	
		glEvalCoord1f((GLfloat)i / number);
	}
	glEnd();
	glPointSize(1.0);
	glColor3f(1, 0.75, 0.8);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&ctrlpoints2[i][0]); 
	}
	glEnd();
}
// draw balloons
const double PI = acos(-1.0);
void balloons() {
	float R1 = 35.0f;  //Radius
	int n1 = 100;     //Accuracy of drawing circles with polygons
	glColor3f(0.89, 0.09, 0.05);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)     //math calculation
	{
		glVertex2f(100 + R1 * cos(2 * PI * i / n1), 325 + R1 * sin(2 * PI * i / n1));
	}
	glEnd();
	float R2 = 35.0f;
	int n2 = 100;     
	glColor3f(0.89, 0.09, 0.05);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n2; i++) 
	{
		glVertex2f(500 + R2 * cos(2 * PI * i / n2), 325 + R2 * sin(2 * PI * i / n2));
	}
	glEnd();
}
//draw trees
void tree(){
	glBegin(GL_TRIANGLES);      //Tree shape
	glColor3f(0.13, 0.55, 0.13);
	glVertex2f(300, 350);
	glVertex2f(230, 270);
	glVertex2f(370, 270);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.13, 0.55, 0.13);
	glVertex2f(300, 280);
	glVertex2f(210, 190);
	glVertex2f(390, 190);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.13, 0.55, 0.13);
	glVertex2f(300, 200);
	glVertex2f(180, 100);
	glVertex2f(420, 100);
	glEnd();
	glColor3f(0.6, 0.4, 0.2);
	glBegin(GL_POLYGON);      //Tree trunk
	glVertex2f(275, 0);
	glVertex2f(275, 100);
	glVertex2f(320, 100);
	glVertex2f(320, 0);
	glEnd();
}
//Keyboard and mouse interaction
float r = 0;
GLfloat step = 1; // declare step
GLfloat step1 = 1; 
int time_interval = 16; // declare refresh interval in ms
void OnTimer(int value) {
	r += step;
	if (r >= 360)
		r = 0;
	else if (r <= 0)
		r = 359;
	glutTimerFunc(time_interval, OnTimer, 1);
}
int xd = 0, yd = 0;	//Global Variables
//draw cake and control
void getcake() {
	glColor3f(255.0/255.0, 180.0/255.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(320 + xd, 130 + yd);
	glVertex2f(350 + xd, 120 + yd);
	glVertex2f(350 + xd, 105 + yd);
	glVertex2f(320 + xd, 115 + yd);
	glEnd();
	glColor3f(255.0 / 255.0, 227.0 / 255.0, 132.0 / 255.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(320 + xd, 130 + yd);
	glVertex2f(350 + xd, 140 + yd);
	glVertex2f(350 + xd, 120 + yd);
	glEnd();
}
// keyboard interaction
void keyboard_input(unsigned char key, int x, int y) {
	//flower interaction button
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'e' || key == 'E')// change direction of movement
		step = -step;
	else if (key == 'z' || key == 'Z')// stop
		step = 0;
	else if (key == 'r' || key == 'R')// set step
		step = 5;
	//Arm interaction button
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'i' || key == 'I') {
		step1++;
		if (step1 > 4)
			step1 = 4;              //range of change
	}
	else if (key == 'j' || key == 'J') {
		step1--;
		if (step1 < 2)
			step1 = 2;
	}
	switch (key)
	{
	case 'w':yd += 15; break;
	case 's':yd -= 15; break;
	case 'a':xd -= 15; break;
	case 'd':xd += 15; break;
	}
	glutPostRedisplay();
}
//Change flower rotation speed
void mouse_input(int button, int state, int x, int y) { // mouse interaction
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && step >= -15)
		step -= 1; // decrement step
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON && step <= 15)
		step += 1; // increment step
}
//draw flowers
void flowers() { //Six Petal Flower
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(450, 50);
	glVertex2f(450, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(520, 50);
	glVertex2f(520, 0);
	glEnd();
	glPushMatrix();
	glTranslatef(520, 50, 0);
	glRotatef(r, 0, 0, 1);
	glColor3f(0.54, 0.17, 0.89);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//flower2
	glPushMatrix();
	glTranslatef(450, 50, 0);
	glRotatef(-r, 0, 0, 1);
	glColor3f(0.54, 0.17, 0.89);
	glColor3f(0.54, 0.17, 0.89);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(15, 25);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//Stamens
	float R1 = 5.0f;
	int n1 = 100;     
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)     
	{
		glVertex2f(450 + R1 * cos(2 * PI * i / n1), 50 + R1 * sin(2 * PI * i / n1));
	}
	glEnd();
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)     
	{
		glVertex2f(520 + R1 * cos(2 * PI * i / n1), 50 + R1 * sin(2 * PI * i / n1));
	}
	glEnd();
	//flower's leaves
	glColor3f(0.42, 0.56, 0.14);
	glBegin(GL_TRIANGLES);
	glVertex2f(430, 0);
	glVertex2f(430, 20);
	glVertex2f(455, 0);
	glEnd();
	glColor3f(0.42, 0.56, 0.14);
	glBegin(GL_TRIANGLES);
	glVertex2f(470, 0);
	glVertex2f(470, 20);
	glVertex2f(445, 0);
	glEnd();
	glColor3f(0.42, 0.56, 0.14);
	glBegin(GL_TRIANGLES);
	glVertex2f(500, 0);
	glVertex2f(500, 20);
	glVertex2f(525, 0);
	glEnd();
	glColor3f(0.42, 0.56, 0.14);
	glBegin(GL_TRIANGLES);
	glVertex2f(540, 0);
	glVertex2f(540, 20);
	glVertex2f(515, 0);
	glEnd();
}
//draw a person's face
void face() {
	float R1 = 45.0f;
	int n1 = 100;     
	glColor3f(188.0 / 255, 143.0 / 255, 143.0 / 255.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)     
	{
		glVertex2f(80 + R1 * cos(2 * PI * i / n1), 150 + R1 * sin(2 * PI * i / n1));
	}
	glEnd();
	//mouth
	float r2 = 12.0f;
	glColor3f(0.98, 0.94, 0.93);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)     
	{
		glVertex2f(92 + r2 * cos(2 * PI * i / n1), 118 + r2 * sin(2 * PI * i / n1));
	}
	glEnd();
	//star eyes
	glColor3f(255.0 / 255.0, 215.0 / 255.0, 0.0 / 255.0);
	glBegin(GL_TRIANGLES);
	double x, y, zx, zy, m = PI / 2 - 2 * PI / 5, n, r1, p, r;
	p = PI / 2 - PI / 5;
	//n = 2 * m;
	r1 = 20 * sin(m); // Outer circle radius
	r = r1 / sin(p); // Radius of the circle where the five corners are located
	int i, j;
	for (i = 0; i < 10; i++) {
		zx = 60 + r * cos(p); 
		zy = 160 + r * sin(p); //Five corners of the inner circle
		x = 60 + 30 * cos(m);
		y = 160 + 30 * sin(m); //Five corners of the outer ring
		glVertex2f(x, y);
		glVertex2f(zx, zy);
		glVertex2f(60, 160); // Location
		if (i % 2 == 0)
			m += 2 * PI / 5;
		else
			p += 2 * PI / 5;
	}
	glEnd();
	glColor3f(255.0 / 255.0, 215.0 / 255.0, 0.0 / 255.0);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 10; i++) {
		zx = 118 + r * cos(p);
		zy = 160 + r * sin(p);
		x = 118 + 30 * cos(m);
		y = 160 + 30 * sin(m);
		glVertex2f(x, y);
		glVertex2f(zx, zy);
		glVertex2f(118, 160);
		if (i % 2 == 0)
			m += 2 * PI / 5;
		else
			p += 2 * PI / 5;
	}
	glEnd();  //the second star eye
}
//draw a body and left arm
GLfloat handpoints1[4][3] = { // 4 points to define a cubic Bezier curve
{ 60.0, 120.0, 0.0 }, // Point 0
{ 40.0, 90.0, 0.0 }, // Point 1
{ 55.0, 80.0, 0.0 }, // Point 2
{ 80.0, 50.0, 0.0 } }; // Point 3
void myinit3(void) {
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &handpoints1[0][0]);
	glEnable(GL_MAP1_VERTEX_3); // Enable the evaluator.
}
void newbody() { //body
	glColor3f(188.0 / 255, 143.0 / 255, 143.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(55.0, 120.0);
	glVertex2f(45.0, 0.0);
	glVertex2f(115.0, 0.0);
	glVertex2f(110.0, 120.0);
	glEnd();
	//arm
	glLineWidth(8);
	glColor3f(25.0 / 255, 25.0 / 255, 112.0 / 255.0);
	glBegin(GL_LINE_STRIP);
	int number = 100;

	for (int i = 0; i <= number; i++) {
	
		glEvalCoord1f((GLfloat)i / number);
	}
	glEnd();
	//Plot 4 Points
	glPointSize(1.0);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&handpoints1[i][0]); // Draw each control point
	}
	glEnd();
	float R1 = 5.0f;
	int n1 = 100;     
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n1; i++)    
	{
		glVertex2f(80 + R1 * cos(2 * PI * i / n1), 50 + R1 * sin(2 * PI * i / n1));
	}
	glEnd();
}
// the greeting right hand which can be controlled
GLfloat handpoints2[4][3] = { // 4 points to define a cubic Bezier curve
{ 110.0, 120.0, 0.0 }, // Point 0
{ 150.0, 110.0, 0.0 }, // Point 1
{ 140.0, 150.0, 0.0 }, // Point 2
{ 160.0, 200.0, 0.0 } }; // Point 3
void myinit4(void) {
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, step1, &handpoints2[0][0]);
	glEnable(GL_MAP1_VERTEX_3); // Enable the evaluator.
}
void greetinghand() {
	myinit4();
	glLineWidth(8);
	glColor3f(25.0 / 255, 25.0 / 255, 112.0 / 255.0);
	int number = 50;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= number; i++) {
		
		glEvalCoord1f((GLfloat)i / number);
	}
	glEnd();
	glPointSize(1.0);
	glColor3f(1, 0.75, 0.8);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&handpoints2[i][0]); // Draw each control point
	}
	glEnd();
}

void display() {
	//window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 400);
	glClearColor(1, 0.75, 0.8, 0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	//Graphic elements
	greetinghand();
	myinit3();
	newbody();
	face();

	balloons();
	myinit1();
	balloonstring1();
	myinit2();
	balloonstring2();

	tree();
	text();
	flowers();
	getcake();
	
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 400);
	glutCreateWindow("My New Year¡¯s Greeting Card");
	glutIdleFunc(when_in_mainloop);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_input);
	glutMouseFunc(mouse_input);
	glutTimerFunc(time_interval, OnTimer, 1);
	glutMainLoop();
}
