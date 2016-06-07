#include <time.h>
#include <math.h>
#include <GL/glut.h>

// ZMIENNE GLOBALNE INICJOWANE W FUNKCJI INIT

// tytul okna
char title[] = "RU";

// limit klatek na sekunde 
// (w celu zapewnienia stalej szybkosci animacji i obrotu)
float fps_limit;

// rozmiar okna
unsigned int width;
unsigned int height;

// pozycja okna
int position_x;
int position_y;

// polozenie kamery
float pos[3];
float look[3];
float side_up[3];
float angle[2];	
float distance;

// dopuszczalna zmiana parametrow polozenia kamery na klatke
float delta_distance;
float delta_angle[2];

float letters_width;
float letters_height;
float letters_depth;

float square[] = {
		 0.0,  0.0, 0.0,
         1.0,  0.0, 0.0,	
         1.0,  1.0, 0.0,
         0.0,  1.0, 0.0 
        };

unsigned short square_idx[] = {0, 1, 2, 3}; 

float triangle[] = {
		 0.0,  0.0, 0.0,
         1.0,  0.0, 0.0,	
         1.0,  1.0, 0.0
        };

unsigned short triangle_idx[] = {0, 1, 2}; 

// zainicjowanie zmiennych dotyczacych okna
void init_window()
{
	fps_limit = 60.0;
	width = 400;
	height = 300;
	position_x = 100;
	position_y = 100;
};


// zainicjowanie zmiennych dotyczacych kamery
void init_camera()
{
	distance = 30.0;
	delta_distance = 0.5;
	angle[0] = 0;
	angle[1] = 0;

	delta_angle[0] = 0.1;
	delta_angle[1] = 0.1;

	look[0] = 0.0;
	look[1] = 0.0;
	look[2] = 0.0;

	side_up[0] = 0.0;
	side_up[1] = 1.0;
	side_up[2] = 0.0;
};


// wyliczenie nowej pozycji kamery
void camera_calculate_pos()
{
	pos[0] = sin(angle[0]) * distance;
	pos[1] = 0;
	pos[2] = cos(angle[0]) * distance;

	pos[0] = pos[0] * cos(angle[1]);
	pos[1] = sin(angle[1]) * distance;
	pos[2] = pos[2] * cos(angle[1]);
}


// przesuniecie kamery w lewo
void camera_left()
{
	angle[0] -= delta_angle[0];
	camera_calculate_pos();
};


// przesuniecie kamery w prawo
void camera_right()
{
	angle[0] += delta_angle[0];
	camera_calculate_pos();
};


// przesuniecie kamery w gore
void camera_up()
{
	angle[1] += delta_angle[1];
	if(angle[1] > 1.57)
		angle[1] = 1.57;

	camera_calculate_pos();
};


// przesuniecie kamery w dol
void camera_down()
{
	angle[1] -= delta_angle[1];
	if(angle[1] < -1.57)
		angle[1] = -1.57;

	camera_calculate_pos();
};



// przyblizenie kamery
void camera_closer()
{
	distance -= delta_distance;
	if(distance < 0.1)
		distance = 0.1;

	camera_calculate_pos();
};


// oddalenie kamery
void camera_further()
{
	distance += delta_distance;
	if(distance > 100)
		distance = 100;

	camera_calculate_pos();
};


// funkcja obslugujaca zmiane rozmiaru okna
void window_resize(int new_width, int new_height)
{
	width = new_width;
	height = new_height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);		
	gluPerspective(90.0, (float) width / (float) height, 0.01, 1000.0);
};


// funkcja obslugi klawiszy
void normal_keys(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '+':
		case '=':
			camera_closer();
			break;
		case '-':
			camera_further();
			break;
	};
};


// funkcja obslugi klawiszy specjalnych
void specjal_keys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			camera_right();
			break;
		case GLUT_KEY_LEFT:
			camera_left();
			break;
		case GLUT_KEY_UP:
			camera_up();
			break;
		case GLUT_KEY_DOWN:
			camera_down();
			break;
	};
};



// rysowanie kwadratu z uzyciem tabeli wierzcholkow
void draw_square()
{
	glVertexPointer(3, GL_FLOAT, 0, square);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, square_idx);
};


// rysowanie trojkata z uzyciem tabeli wierzcholkow
void draw_triangle()
{
	glVertexPointer(3, GL_FLOAT, 0, triangle);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, triangle_idx);
};


// funkcja rysujaca przod (tyl) litery R
void draw_R_face()
{
	float w_size = letters_width * 0.25;
	float h_size = letters_height * 0.125;
	
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glScalef(w_size, letters_height, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size, letters_height, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glScalef(h_size, w_size * 2, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size * 3, letters_height, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glScalef(h_size, w_size, 1.0);
		draw_triangle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size * 4, letters_height - h_size, 0.0);
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glScalef(w_size, h_size * 3, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size * 4, letters_height - h_size * 4, 0.0);
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glScalef(w_size, h_size, 1.0);
		draw_triangle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size, letters_height - h_size * 4, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glScalef(h_size, w_size * 2, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size * 4, letters_height - h_size * 5, 0.0);
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glScalef(w_size, h_size * 3, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(w_size * 3, letters_height - h_size * 4, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glScalef(w_size, h_size, 1.0);
		draw_triangle();
	glPopMatrix();

};

// funkcja rysujaca boki litery R
void draw_R_side()
{
	return;
// pionowe sciany
	glPushMatrix();
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(4.0, 20.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.0, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(4.0, 20.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(4.0, 20.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0, 11.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(4.0, 6.0, 1.0);
		draw_square();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(12.0, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(4.0, 8.0, 1.0);
		draw_square();
	glPopMatrix();

// poziome sciany
	glPushMatrix();
		glTranslatef(0.0, 20.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(9.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 17.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(9.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 11.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(9.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 8.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(9.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0, 0.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 4.0, 1.0);
		draw_square();
	glPopMatrix();
	
// skosne sciany
	glPushMatrix();
		glTranslatef(9.0, 20.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		glScalef(3.0 * sqrt(2), 4.0, 1.0);
		draw_square();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(9.0, 8.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glScalef(3.0 * sqrt(2), 4.0, 1.0);
		draw_square();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0, 11.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		glScalef(3.0 * sqrt(2), 4.0, 1.0);
		draw_square();
	glPopMatrix();
};

// rysowanie litery R
void letter_R()
{
// przod litery
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, 2.0);
		draw_R_face();
	glPopMatrix();
	
// tyl litery
	glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -2.0);
		draw_R_face();
	glPopMatrix();

// boki litery
	glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		glTranslatef(0.0, 0.0, -2.0);
		draw_R_side();
	glPopMatrix();
};


void scena()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(pos[0], pos[1], pos[2],
			  look[0], look[1], look[2],
			  side_up[0], side_up[1], side_up[2]); 
	
    glColor3f(0.0, 0.0, 0.0);
	letter_R();
    
/*    glTranslatef(5.0, 0, 0);
	glColor3f(1.0, 0.0, 0.0);
	kwadrat();*/
    
	glFlush();
	glutSwapBuffers(); 
}



void render_frame(int)
{
	clock_t start_frame;
	clock_t end_frame;
	clock_t frame_time;
	
	start_frame = clock();
	
	glutPostRedisplay();
	
	end_frame = clock();

	int max_frame_time = 1000 / fps_limit;	
	if(max_frame_time > frame_time)
		glutTimerFunc(max_frame_time - (end_frame - start_frame), render_frame, 0);
	else
		glutTimerFunc(1, render_frame, 0);
};





void init(int argc, char *argv[])
{
	letters_width = 16.0;
	letters_height = 24.0;
	letters_depth = 4.0;
	
	init_camera();
	init_window();
	camera_calculate_pos();
	
	glutInit(&argc, argv);  

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize(width, height);
	glutInitWindowPosition(position_x, position_y);
	
	glutCreateWindow(title);

	glutDisplayFunc(scena);
	glutReshapeFunc(window_resize);
	glutKeyboardFunc(normal_keys);
	glutSpecialFunc(specjal_keys);
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);

    glutTimerFunc(1000 / fps_limit, render_frame, 0);
};


int main(int argc, char** argv)
{
	init(argc, argv);
	glutMainLoop();
}
