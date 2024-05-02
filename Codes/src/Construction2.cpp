#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

// Define global variables for angles of rotation
GLfloat First_Element = 0.0f;
GLfloat Second_Element = 90.0f;
GLfloat Third_Element = 0.0f;
GLfloat Fourth_Element = 0.0f;
GLfloat Fifth_Element = 0.0f;
GLfloat Sixth_Element = 0.0f;

GLfloat Camera_x = -1.0;
GLfloat Camera_y = -1.0;
GLfloat Camera_z = -5.0;

GLfloat Look_x = 0.0;
GLfloat Look_y = 1.0;
GLfloat Look_z = 0.0;

GLfloat UP_vector_x = 0.0;
GLfloat UP_vector_y = 1.0;
GLfloat UP_vector_z = 0.0;


GLfloat TTTT = 0;

// Define function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
            First_Element += 5.0f;
            std::cout << "First_Element: " << First_Element << "\n";
            if (First_Element > 359.0f) First_Element -= 360.0f;
            break;
        case 'c':
            First_Element -= 5.0f;
            std::cout << "First_Element: " << First_Element << "\n";
            if (First_Element < 1.0f) First_Element += 360.0f;
            break;
        case 'a':
            Second_Element += 5.0f;
            std::cout << "Second_Element: " << Second_Element << "\n";
            if (Second_Element > 359.0f) Second_Element -= 360.0f;
            break;
        case 'd':
            Second_Element -= 5.0f;
            std::cout << "Second_Element: " << Second_Element << "\n";
            if (Second_Element < 1.0f) Second_Element += 360.0f;
            break;
        case 'q':
            Third_Element += 5.0f;
            std::cout << "Third_Element: " << Third_Element << "\n";
            if (Third_Element > 359.0f) Third_Element -= 360.0f;
            break;
        case 'e':
            Third_Element -= 5.0f;
            std::cout << "Third_Element: " << Third_Element << "\n";
            if (Third_Element < 1.0f) Third_Element += 360.0f;
            break;


        case 't':
            Camera_x += 0.1f;
            std::cout << "Camera_x: " << Camera_x << "\n";
            if (Camera_x > 10.0f) Camera_x -= 10.0f;
            break;
        case 'y':
            Camera_x -= 0.1f;
            std::cout << "Camera_x: " << Camera_x << "\n";
            if (Camera_x < -5.0f) Camera_x += 5.0f;
            break;
        case 'g':
            Camera_y += 0.1f;
            std::cout << "Camera_y: " << Camera_y << "\n";
            if (Camera_y > 10.0f) Camera_y -= 10.0f;
            break;
        case 'h':
            Camera_y -= 0.1f;
            std::cout << "Camera_y: " << Camera_y << "\n";
            if (Camera_y < -5.0f) Camera_y += 5.0f;
            break;
        case 'b':
            Camera_z += 0.1f;
            std::cout << "Camera_z: " << Camera_z << "\n";
            if (Camera_z > 10.0f) Camera_z -= 10.0f;
            break;
        case 'n':
            Camera_z -= 0.1f;
            std::cout << "Camera_z: " << Camera_z << "\n";
            if (Camera_z < -5.0f) Camera_z += 5.0f;
            break;
    }

    glutPostRedisplay(); // Redraw scene
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    glMatrixMode(GL_PROJECTION); // Set projection matrix
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5); // Orthographic projection
    glMatrixMode(GL_MODELVIEW); // Set modelview matrix
}

void drawCube(float size) {
    glBegin(GL_QUADS);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glEnd();
}

void drawArmSegment(float length, float width) {
    glPushMatrix();
    glScalef(length, width, width);
    drawCube(1.0f);
    glutSolidCone(1.0f,2.0f,1.0f,10);
    glPopMatrix();
}

void drawJoint(float size) {
    glPushMatrix();
    glScalef(size, size, size);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

    // glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Load identity matrix


   gluLookAt(Camera_x, Camera_y, Camera_z,   //Camera Position
              Look_x, Look_y, Look_z,   //Look at point
              UP_vector_x, UP_vector_y, UP_vector_z);  //Up Vector

    // Draw under Base
    glColor3f(1.0, 0.5, 0.0); // Yellow color
    glTranslatef(0.0, -4.0, 0.0);
    glRotated(90, 0.0, 0.0, 1.0);
    drawArmSegment(2.50f, 0.7f);
    
    // Drawing Base
    glTranslatef(1.25, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5); // white color
    glRotatef(-90.0f, 0.0, 0.0, 1.0); // Rotate around z-axis
    glRotatef(First_Element, 0.0, 1.0, 0.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw small link between base and shoulder
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.4, 0.0, 0.0);
    drawArmSegment(0.4f, 0.5f);

   // Draw Shoulder
    glColor3f(0.5, 0.5, 0.5); // Gray color
    glTranslatef(0.4, 0.0, 0.0);
    glRotatef(Second_Element, 0.0, 1.0, 1.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw first Link between Shoulder and Elbow
    glColor3f(1.0, 0.5, 0.0); // Yellow color
    glTranslatef(1, 0.0, 0.0);
    drawArmSegment(2.0f, 0.5f);

    // Draw Elbow
    glTranslatef(1, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5); // Yellow color
    // glRotatef(90, 0.0, 0.0, 1.0); // Rotate around z-axis
    glRotatef(Third_Element, 0.0, 1.0, 0.0); // Rotate around z-axis
    drawJoint(0.7f);    

    // // Draw small link sticked to Elbow
    // glColor3f(1.0, 0.5, 0.0); // Gray color
    // glTranslatef(0.0, 0.4, 0.0);
    // drawArmSegment(0.4f, 0.5f);

    // // Draw  Link to the Wrists
    // glColor3f(1.0, 0.5, 0.0); // Yellow color
    // glTranslatef(0.8, 0.75, 0.0);
    // glRotatef(90, 0.0, 1.0, 0.0); // Rotate around z-axis
    // drawArmSegment(2.0f, 0.5f);

    glutSwapBuffers(); // Swap buffers
}

void update(int value) {
    glutPostRedisplay(); // Redraw scene
    glutTimerFunc(16, update, 0); // Call update function recursively
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(900, 900); // Set window size
    glutCreateWindow("OpenGL Robot Arm"); // Create window with title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Timer for animation


    glutKeyboardFunc(keyboard); // Register keyboard callback function

    glutMainLoop(); // Enter main event loop

    return 0;
}