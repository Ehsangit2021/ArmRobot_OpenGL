#include <GL/glut.h>
#include <cmath>

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
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light source 0

    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glMatrixMode(GL_PROJECTION); // Set projection matrix
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW); // Set modelview matrix
}

void drawBase() {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    glutSolidCube(4.0);
    glPopMatrix();
}

void drawArmSegment(float length, float width) {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glPushMatrix();
    glTranslatef(0.0, 0.0, -length / 2);
    glutSolidCube(width);
    glPopMatrix();

    glTranslatef(0.0, 0.0, -length);
    gluCylinder(width / 2, width / 2, length, 20);
}

void drawJoint(float size) {
    glColor3f(0.5, 0.5, 0.5); // Grey color
    glutSolidSphere(size, 20, 20);
}

void drawCylinder(GLfloat baseRadius, GLfloat topRadius, GLfloat height, GLint slices) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric, baseRadius, topRadius, height, slices, 1);
    gluDeleteQuadric(quadric);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers

    glLoadIdentity(); // Load identity matrix

    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0); // Set camera position and orientation

    // Draw base
    drawBase();

    // Draw first arm segment
    glPushMatrix();
    glTranslatef(0.0, 0.0, 2.0);
    glRotatef(baseAngle, 0.0, 0.0, 1.0);
    drawArmSegment(2.0f, 0.5f);
    drawJoint(0.6f);

    // Draw second arm segment
    glTranslatef(0.0, 0.0, 2.0);
    glRotatef(shoulderAngle, 0.0, 1.0, 0.0);
    drawArmSegment(2.0f, 0.4f);
    drawJoint(0.5f);

    // Draw third arm segment
    glTranslatef(0.0, 0.0, 2.0);
    glRotatef(elbowAngle, 0.0, 1.0, 0.0);
    drawArmSegment(2.0f, 0.4f);
    drawJoint(0.5f);

    // Draw fourth arm segment
    glTranslatef(0.0, 0.0, 2.0);
    glRotatef(wrist1Angle, 0.0, 1.0, 0.0);
    drawArmSegment(1.5f, 0.3f);
    drawJoint(0.4f);

    // Draw fifth arm segment
    glTranslatef(0.0, 0.0, 1.5);
    glRotatef(wrist2Angle, 0.0, 0.0, 1.0);
    drawArmSegment(1.5f, 0.3f);
    drawJoint(0.4f);

    // Draw sixth arm segment
    glTranslatef(0.0, 0.0, 1.5);
    glRotatef(wrist3Angle, 0.0, 1.0, 0.0);
    drawArmSegment(1.0f, 0.2f);
    drawJoint(0.3f);
    glPopMatrix();

    glutSwapBuffers(); // Swap buffers
}

void update(int value) {
    glutPostRedisplay(); // Redraw scene
    glutTimerFunc(16, update, 0); // Call update function recursively
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
   
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("UR10e Robot Arm"); // Create window with title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Timer for animation
    glutKeyboardFunc(keyboard); // Register keyboard callback function

    glutMainLoop(); // Enter main event loop

    return 0;
}