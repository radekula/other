#include <time.h>
#include <math.h>
#include <GL/glut.h>

// tytul okna
char title[] = "Lights - RU";


// limit klatek na sekunde 
// (w celu zapewnienia stalej szybkosci animacji i obrotu)
float fps_limit = 60;


// rozmiar okna
unsigned int width = 400;
unsigned int height = 400;


// pozycja okna
int position_x = 100;
int position_y = 100;


// parametry
float letters_width = 10.0;
float letters_height = 20.0;
float letters_depth = 4.0;
float base_width = 4.0;

// polozenie kamery
float distance = 30.0;
float pos[3];
float look[3] = {0.0, 0.0, 0.0};
float side_up[3] = {0.0, 1.0, 0.0};
float angle[2] = {0.0, 0.0};

float delta_distance = 0.5;
float delta_angle[2] = {0.1, 0.1};


bool light0_on = true;


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
        case '1':
            light0_on = true;
            break;
        case '0':
            light0_on = false;
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

// swiatlo biale kierunkowe
void light_0()
{
    float LightAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
    float LightEmission[] = { 0.5, 0.5, 0.5, 1.0 };
    float LightDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    float LightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    float LightPosition[]= { 10.0, 20.0, 0.0, 0.0 };
    float LightSpotDirection[]= { 0.0, -1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 120.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightSpotDirection);
};


// swiatlo czerwone punktowe
void light_1()
{
    float LightAmbient[] = { 0.1, 0.0, 0.0, 1.0 };
    float LightDiffuse[] = { 0.5, 0.0, 0.0, 1.0 };
    float LightSpecular[] = { 1.0, 0.5, 0.5, 1.0 };
    float LightPosition[]= { 10.0, 4.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
};


// swiatlo niebieskie punktowe
void light_2()
{
    float LightAmbient[] = { 0.0, 0.0, 0.1, 1.0 };
    float LightDiffuse[] = { 0.0, 0.0, 0.8, 1.0 };
    float LightSpecular[] = { 0.5, 0.5, 1.0, 1.0 };
    float LightPosition[]= { -10.0, 4.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
};


void light_red_mat()
{
    glColor4f(1.0, 0.3, 0.3, 1.0);

    float MatAmbient[] = { 0.2f, 0.1f, 0.1f, 1.0f };
    float MatDiffuse[] = { 0.8f, 0.4f, 0.4f, 1.0f };
    float MatSpecular[] = { 0.0f, 0.0f, 0.0f, 0.3f };
    float MatShininess = 0;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
};


void yellow_shining()
{
    glColor4f(1.0, 1.0, 0.0, 1.0);

    float MatAmbient[] = { 0.2f, 0.2f, 0.1f, 1.0f };
    float MatDiffuse[] = { 0.8f, 0.8f, 0.4f, 1.0f };
    float MatSpecular[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    float MatShininess = 127;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
};


void light_blue()
{
    glColor4f(0.5, 0.5, 1.0, 1.0);

    float MatAmbient[] = { 0.1f, 0.1f, 0.2f, 1.0f };
    float MatDiffuse[] = { 0.4f, 0.4f, 0.8f, 1.0f };
    float MatSpecular[] = { 0.5f, 0.5f, 1.0f, 1.0f };
    float MatShininess = 60;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, MatShininess);
};


// funkcja ryzujaca scene
void scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(pos[0], pos[1], pos[2],
              look[0], look[1], look[2],
              side_up[0], side_up[1], side_up[2]); 


    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);

    light_0();
    light_1();
    light_2();
    
    if(!light0_on)
        glDisable(GL_LIGHT0);
    
// trzy kule
    glPushMatrix();
        light_red_mat();
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        yellow_shining();
        glTranslatef(0.0, 6.0, 0.0);
        glutSolidSphere(4.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        light_blue();
        glTranslatef(0.0, 10.0, 0.0);
        glutSolidSphere(2.0, 100, 100);
    glPopMatrix();

// dwa szesciany
    glPushMatrix();
        light_red_mat();
        glTranslatef(-10.0, 4.0, -10.0);
        glutSolidCube(8.0);
    glPopMatrix();

    glPushMatrix();
        yellow_shining();
        glTranslatef(10.0, 4.0, 10.0);
        glutSolidCube(4.0);
    glPopMatrix();

// dwa stozki
    glPushMatrix();
        light_red_mat();
        glTranslatef(10.0, 0.0, -10.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(4.0, 8.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        yellow_shining();
        glTranslatef(-10.0, 2.0, 10.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(2.0, 4.0, 100, 100);
    glPopMatrix();

    glFlush();
    glutSwapBuffers(); 
}



// funkcja wykonywana okresowo wymuszajaca rysowanie 1 klatki
// stala ilosc klatek na sekunde gwarantuje animacje kamery ze stala predkoscia
void render_frame(int)
{
    clock_t start_frame;
    clock_t end_frame;
    clock_t frame_time;
    
    start_frame = clock();
    
    glutPostRedisplay();
    
    end_frame = clock();

    frame_time = end_frame - start_frame;

    int max_frame_time = 1000 / fps_limit;    
    if(max_frame_time > frame_time)
        glutTimerFunc(max_frame_time - (end_frame - start_frame), render_frame, 0);
    else
        glutTimerFunc(1, render_frame, 0);
};


// funkcja inicjujaca program
void init(int argc, char *argv[])
{
    camera_calculate_pos();
    
    glutInit(&argc, argv);  

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(width, height);
    glutInitWindowPosition(position_x, position_y);
    
    glutCreateWindow(title);

    glutDisplayFunc(scene);
    glutReshapeFunc(window_resize);
    glutKeyboardFunc(normal_keys);
    glutSpecialFunc(specjal_keys);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glutTimerFunc(1000 / fps_limit, render_frame, 0);
};


// glowna funkcja programu
int main(int argc, char** argv)
{
    init(argc, argv);
    glutMainLoop();
}
