#include <GL/glut.h>

// Define global variables for angles of rotation
GLfloat baseAngle_z = 0.0f;
GLfloat baseAngle_y = 0.0f;
GLfloat baseAngle_x = 0.0f;
GLfloat joint1Angle = 0.0f;
GLfloat joint2Angle = 0.0f;
GLfloat joint3Angle = 0.0f;

// Define function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            baseAngle_z += 5.0f;
            break;
        case 'e':
            baseAngle_z -= 5.0f;
            break;
        case 'w':
            baseAngle_y += 5.0f;
            break;
        case 'r':
            baseAngle_y -= 5.0f;
            break;
        case 't':
            baseAngle_x += 5.0f;
            break;
        case 'y':
            baseAngle_x -= 5.0f;
            break;                        
        case 'a':
            joint1Angle += 5.0f;
            break;
        case 'd':
            joint1Angle -= 5.0f;
            break;
        case 'z':
            joint2Angle += 5.0f;
            break;
        case 'c':
            joint2Angle -= 5.0f;
            break;
        case 'x':
            joint3Angle += 5.0f;
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
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glLoadIdentity(); // Load identity matrix

    // Draw base first joint
    glColor3f(1.0, 1.0, 1.0); // Red color
    glRotatef(baseAngle_x, 1.0, 0.0, 0.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw base seconf joint
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.1, 0.0, 0.0);
    glRotatef(baseAngle_z, 0.0, 0.0, 1.0); // Rotate around z-axis
    glRotatef(baseAngle_y, 0.0, 1.0, 0.0); // Rotate around z-axis
    drawJoint(0.7f);

    // Draw first arm segment
    glTranslatef(1.0, 0.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef(joint1Angle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    drawArmSegment(2.0f, 0.5f);

    // Draw first joint
    glColor3f(0.0, 1.0, 0.0); // Green color
    glTranslatef(1.0, 0.0, 0.0);
    drawJoint(0.5f);

    // Draw second arm segment
    glTranslatef(0.75, 0.0, 0.0);
    glTranslatef(-0.75, 0.0, 0.0);
    glRotatef(joint2Angle, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);
    drawArmSegment(1.5f, 0.4f);

    // Draw second joint
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glTranslatef(0.75, 0.0, 0.0);
    drawJoint(0.4f);

    // Draw third arm segment
    glTranslatef(0.5, 0.0, 0.0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(joint3Angle, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    drawArmSegment(1.0f, 0.3f);

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