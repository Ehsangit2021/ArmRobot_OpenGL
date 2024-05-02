#include <GL/glut.h>
#include <iostream>

// Define global variables for angles of rotation
GLfloat baseAngle = 0.0f;
GLfloat joint1Angle = 0.0f;
GLfloat joint2Angle = 0.0f;
GLfloat joint3Angle = 0.0f;

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
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glLoadIdentity(); // Load identity matrix

    // Draw base
    glColor3f(1.0, 0.0, 0.0); // Red color
    drawJoint(1.0f);

    // Draw first arm segment
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(joint1Angle, 0.0, 0.0, 1.0);
    drawArmSegment(2.0f, 0.5f);

    // Draw first joint
    glColor3f(0.0, 1.0, 0.0); // Green color
    glTranslatef(2.0, 0.0, 0.0);
    drawJoint(0.5f);

    // Draw second arm segment
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(joint2Angle, 0.0, 0.0, 1.0);
    drawArmSegment(1.5f, 0.4f);

    // Draw second joint
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glTranslatef(1.5, 0.0, 0.0);
    drawJoint(0.4f);

    // Draw third arm segment
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(joint3Angle, 0.0, 0.0, 1.0);
    drawArmSegment(1.0f, 0.3f);

    glutSwapBuffers(); // Swap buffers
}

void update(int value) {
    // Increment angles for animation
    baseAngle += 0.5f;
    joint1Angle += 1.0f;
    joint2Angle -= 0.5f;
    joint3Angle += 0.8f;

    if (baseAngle > 360) baseAngle -= 360;
    if (joint1Angle > 360) joint1Angle -= 360;
    if (joint2Angle < -90) joint2Angle = -90;
    if (joint3Angle > 90) joint3Angle = 90;

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

    glutMainLoop(); // Enter main event loop

    return 0;
}