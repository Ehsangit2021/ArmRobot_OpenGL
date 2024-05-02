#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

// Define global variables for joint angles
GLfloat baseAngle = 0.0f;
GLfloat shoulderAngle = 0.0f;
GLfloat elbowAngle = 0.0f;
GLfloat wrist1Angle = 0.0f;
GLfloat wrist2Angle = 0.0f;
GLfloat wrist3Angle = 0.0f;

// Define function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            baseAngle += 5.0f;
            break;
        case 'e':
            baseAngle -= 5.0f;
            break;
        case 'w':
            shoulderAngle += 5.0f;
            break;
        case 's':
            shoulderAngle -= 5.0f;
            break;
        case 'a':
            elbowAngle += 5.0f;
            break;
        case 'd':
            elbowAngle -= 5.0f;
            break;
        case 'r':
            wrist1Angle += 5.0f;
            break;
        case 'f':
            wrist1Angle -= 5.0f;
            break;
        case 't':
            wrist2Angle += 5.0f;
            break;
        case 'g':
            wrist2Angle -= 5.0f;
            break;
        case 'y':
            wrist3Angle += 5.0f;
            break;
        case 'h':
            wrist3Angle -= 5.0f;
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

void drawCylinder(float radius, float height) {
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, radius, radius, height, 20, 20);
    gluDeleteQuadric(obj);
}

void drawBase() {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    drawCube(4.0);
    glPopMatrix();
}

void drawArmSegment(float length, float width) {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glPushMatrix();
    glTranslatef(0.0, 0.0, -length / 2);
    drawCube(width);
    glPopMatrix();
    glTranslatef(0.0, 0.0, -length);
    drawCylinder(width / 2, length);
}

void drawJoint(float size) {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glutSolidSphere(size, 20, 20);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glLoadIdentity(); // Load identity matrix

    // Draw base
    drawBase();

    // Draw first arm segment
    glPushMatrix();

    glTranslatef(1.0, 0.0, 2.0);
    glRotatef(baseAngle, 0.0, 0.0, 1.0);
    drawArmSegment(2.0f, 0.5f);
    drawJoint(0.6f);

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
    glutCreateWindow("UR10e Robot Arm"); // Create window with title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Timer for animation
    glutKeyboardFunc(keyboard); // Register keyboard callback function

    glutMainLoop(); // Enter main event loop

    return 0;
}