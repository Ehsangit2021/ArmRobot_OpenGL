#include <GL/glut.h>

// Define global variables for angles of rotation
GLfloat baseAngle = 0.0f;
GLfloat armAngle = 0.0f;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    glMatrixMode(GL_PROJECTION); // Set projection matrix
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5); // Orthographic projection
    glMatrixMode(GL_MODELVIEW); // Set modelview matrix
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glLoadIdentity(); // Load identity matrix

    // Draw base
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Red color
    glRotatef(baseAngle, 0.0, 0.0, 1.0); // Rotate around z-axis
    glutSolidCube(1.0); // Draw cube for base
    glPopMatrix();

    // Draw arm
    glTranslatef(2.0, 0.0, 0.0); // Translate arm to joint position
    glRotatef(armAngle, 0.0, 0.0, 1.0); // Rotate around z-axis
    glColor3f(0.0, 1.0, 0.0); // Green color
    glutSolidCube(2.0); // Draw cube for arm

    glutSwapBuffers(); // Swap buffers
}

void update(int value) {
    // Increment angles for animation
    baseAngle += 1.0f;
    if (baseAngle > 360) baseAngle -= 360;

    armAngle -= 0.5f;
    if (armAngle < -90) armAngle = -90;

    glutPostRedisplay(); // Redraw scene
    glutTimerFunc(16, update, 0); // Call update function recursively
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500); // Set window size
    glutCreateWindow("OpenGL Robot Arm"); // Create window with title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Timer for animation

    glutMainLoop(); // Enter main event loop

    return 0;
}