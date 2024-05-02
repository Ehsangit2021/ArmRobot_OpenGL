#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

// Define global variables for angles of rotation
GLfloat baseAngle_z = 0.0f;
GLfloat baseAngle_y = 0.0f;
GLfloat baseAngle_x = 0.0f;
GLfloat joint1Angle = 0.0f;
GLfloat joint2Angle = 0.0f;
GLfloat joint3Angle = 0.0f;

GLfloat TTTT = 0;

// Define function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            baseAngle_z += 5.0f;
            std::cout << "baseAngle_z: " << baseAngle_z << "\n";
            if (baseAngle_z > 360.0f) baseAngle_z -= 360.0f;
            break;
        case 'e':
            baseAngle_z -= 5.0f;
            std::cout << "baseAngle_z: " << baseAngle_z << "\n";
            if (baseAngle_z < 0.0f) baseAngle_z += 360.0f;
            break;
        case 'w':
            baseAngle_y += 5.0f;
            std::cout << "baseAngle_y: " << baseAngle_y << "\n";
            if (baseAngle_y > 360.0f) baseAngle_y -= 360.0f;
            break;
        case 'r':
            baseAngle_y -= 5.0f;
            std::cout << "baseAngle_y: " << baseAngle_y << "\n";
            if (baseAngle_y < 0.0f) baseAngle_y += 360.0f;
            break;
        case 't':
            baseAngle_x += 5.0f;
            break;
        case 'y':
            baseAngle_x -= 5.0f;
            break;
        case 'v':
            joint3Angle -= 5.0f;
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

    // gluLookAt(-1.0, -1.0, -5.0,   //Camera Position
    //           0.0, 0.0, 0.0,   //Look at point
    //           0.0, 1.0, 0.0);  //Up Vector


    // gluPerspective(30.0f, 800.0f/600.0f, 100.1f, 500.0f);
    // glMatrixMode(GL_MODELVIEW);


    // Draw Stand
    glColor3f(1.0, 0.5, 0.0); // X color
    glTranslatef(0.0, -4.0, 0.0);
    glRotated(90, 0.0, 0.0, 1.0);
    drawArmSegment(3.0f, 0.7f);
    glRotated(-90, 0.0, 0.0, 1.0);

    // Draw base first joint
    glTranslatef(0.0, 1.5, 0.0);
    glColor3f(1.0, 1.0, 1.0); // Red color
    glRotatef(baseAngle_z, 0.0, 1.0, 0.0); // Rotate around z-axis
    glRotatef(baseAngle_x, 0.0, 0.0, 1.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw small link
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.4, 0.0, 0.0);
    drawArmSegment(0.4f, 0.5f);

   // Draw base first joint
    glColor3f(0.5, 0.5, 0.5); // Red color
    glTranslatef(0.4, 0.0, 0.0);

    glRotatef(baseAngle_y, 0.0, 0.0, 1.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw base second joint
    glColor3f(1.0, 0.5, 0.0); // Red color
    // glRotatef(baseAngle_z, 0.0, 0.0, 1.0); // Rotate around z-axis
    glTranslatef(1, 0.0, 0.0);
    drawArmSegment(2.0f, 0.5f);

    glTranslatef(1, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5); // Red color
    drawJoint(0.7f);

    // Draw small link
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.0, 0.4, 0.0);
    drawArmSegment(0.4f, 0.5f);

    glTranslatef(0.0, -0.4, 0.0);
    glColor3f(0.5, 0.5, 0.5); // Red color
    glRotatef(TTTT, 1.0, 0.0, 0.0); // Rotate around z-axis    
    drawJoint(0.7f);

    glRotatef(TTTT, 1.0, 0.0, 0.0); // Rotate around z-axis    

    glTranslatef(0.8, 0.8, 0.0);
    glColor3f(1.0, 0.5, 0.0); // Red color
    drawArmSegment(2.0f, 0.5f);

    glTranslatef(1.0, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5); // Red color
    drawJoint(0.7f);

    // Draw small link
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.0, -0.4, 0.0);
    drawArmSegment(0.4f, 0.5f);
    
    glutSwapBuffers(); // Swap buffers
}

void update(int value) {
    glutPostRedisplay(); // Redraw scene
    glutTimerFunc(16, update, 0); // Call update function recursively
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("OpenGL Robot Arm"); // Create window with title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Timer for animation


    glutKeyboardFunc(keyboard); // Register keyboard callback function

    glutMainLoop(); // Enter main event loop

    return 0;
}