#include <time.h>
#include <math.h>
#include <GL/glut.h>

// tytul okna
char title[] = "RU";


// limit klatek na sekunde 
// (w celu zapewnienia stalej szybkosci animacji i obrotu)
float fps_limit = 60;


// rozmiar okna
unsigned int width = 400;
unsigned int height = 400;


// pozycja okna
int position_x = 100;
int position_y = 100;


// parametry poczatkowe
float distance = 30.0;
float delta_distance = 0.5;

float delta_angle[2] = {0.1, 0.1};

float letters_width = 10.0;
float letters_height = 20.0;
float letters_depth = 4.0;
float base_width = 4.0;


// polozenie kamery
float pos[3];
float look[3];
float side_up[3];
float angle[2];


float cube[] = {
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5,
        
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        
        -0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        
        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,

        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,

        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5
    };

float cube_colors[] = {
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,

        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,

        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,

        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,

        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,

        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0
    };  

unsigned short cube_idx[] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15,
        16, 17, 18, 19,
        20, 21, 22, 23
    };

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
    angle[0] = 0;
    angle[1] = 0;

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


// funkcja rysujaca szescian
void draw_cude()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, cube_idx);
};


// funkcja rysujaca szescian z kolorami
void draw_cude_with_colors()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, cube);
    glColorPointer(3, GL_FLOAT, 0, cube_colors);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, cube_idx);
};





void letter_R()
{
    glScalef(letters_width, letters_height, letters_depth);

    glPushMatrix();
        glTranslatef(-0.4, 0.0, 0.0);
        glScalef(0.2, 1.0, 1.0);
        draw_cude_with_colors();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.45, 0.0);
        glScalef(0.6, 0.1, 1.0);
        draw_cude_with_colors();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -0.05, 0.0);
        glScalef(0.6, 0.1, 1.0);
        draw_cude_with_colors();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.4, 0.2, 0.0);
        glScalef(0.2, 0.4, 1.0);
        draw_cude_with_colors();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.4, -0.3, 0.0);
        glScalef(0.2, 0.4, 1.0);
        draw_cude_with_colors();
    glPopMatrix();
};


void letter_U()
{
    glScalef(letters_width, letters_height, letters_depth);

    glPushMatrix();
        glTranslatef(-0.4, 0.05, 0.0);
        glScalef(0.2, 0.9, 1.0);
        draw_cude_with_colors();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.4, 0.05, 0.0);
        glScalef(0.2, 0.9, 1.0);
        draw_cude_with_colors();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, -0.45, 0.0);
        glScalef(0.6, 0.1, 1.0);
        draw_cude_with_colors();
    glPopMatrix();
};


void base()
{
    glPushMatrix();
        draw_cude();
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

    glPushMatrix();
        glTranslatef(-6.0, 0.0, 0.0);
        letter_R();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(6.0, 0.0, 0.0);
        letter_U();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(0.0, -(letters_height / 2 + 2), 0.0);
        glScalef(letters_width * 3, base_width, letters_width + 2);
        base();
    glPopMatrix();
    
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

    glutTimerFunc(1000 / fps_limit, render_frame, 0);
};


int main(int argc, char** argv)
{
    init(argc, argv);
    glutMainLoop();
}
