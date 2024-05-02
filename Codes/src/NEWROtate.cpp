#include <GL/glut.h>
#include <cmath>

// Define global variables for angles of rotation
GLfloat baseAngle = 0.0f;
GLfloat joint1Angle = 0.0f;
GLfloat joint2Angle = 0.0f;
GLfloat joint3Angle = 0.0f;

// Function to draw a cylinder
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    gluDeleteQuadric(quadric);
}

// Function to draw a single arm segment
void drawArmSegment(float length, float width) {
    glPushMatrix();
    glTranslatef(length / 2.0f, 0.0f, 0.0f); // Move to the end of the previous segment
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate to align with joint
    drawCylinder(width / 2.0f, width / 2.0f, length, 20, 20); // Draw arm segment
    glPopMatrix();
}

// Function to draw a single joint
void drawJoint(float size) {
    glutSolidSphere(size / 2.0f, 20, 20); // Draw joint
}


// Function to draw a single robot arm
void drawRobotArm(float length1, float length2, float length3) {
    // Draw base
    glColor3f(1.0, 0.0, 0.0); // Red color
    drawJoint(1.0f);

    // Draw first arm segment
    glColor3f(0.0, 1.0, 0.0); // Green color
    drawArmSegment(length1, 0.3f);

    // Draw first joint
    glColor3f(0.0, 0.0, 1.0); // Blue color
    drawJoint(0.5f);

    // Draw second arm segment
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    drawArmSegment(length2, 0.3f);

    // Draw second joint
    glColor3f(1.0, 0.0, 1.0); // Magenta color
    drawJoint(0.5f);

    // Draw third arm segment
    glColor3f(0.0, 1.0, 1.0); // Cyan color
    drawArmSegment(length3, 0.3f);
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    glLoadIdentity(); // Load identity matrix

    // Draw four robot arms at different positions and orientations
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 0.0f); // Translate to the first arm position
    glRotatef(baseAngle, 0.0f, 1.0f, 0.0f); // Rotate the first arm around the base
    drawRobotArm(2.0f, 1.5f, 1.0f); // Draw the first robot arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f); // Translate to the second arm position
    glRotatef(baseAngle, 0.0f, 1.0f, 0.0f); // Rotate the second arm around the base
    drawRobotArm(1.5f, 1.0f, 0.5f); // Draw the second robot arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 0.0f); // Translate to the third arm position
    glRotatef(baseAngle, 0.0f, 1.0f, 0.0f); // Rotate the third arm around the base
    drawRobotArm(1.0f, 0.75f, 0.5f); // Draw the third robot arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 0.0f); // Translate to the fourth arm position
    glRotatef(baseAngle, 0.0f, 1.0f, 0.0f); // Rotate the fourth arm around the base
    drawRobotArm(0.5f, 0.4f, 0.3f); // Draw the fourth robot arm
    glPopMatrix();

    glutSwapBuffers(); // Swap buffers
}

// Function to update the animation
void update(int value) {
    baseAngle += 0.5f; // Increment the angle for rotation
    if (baseAngle > 360) baseAngle -= 360; // Ensure the angle stays within 360 degrees

    glutPostRedisplay(); // Mark the current window for redisplay
    glutTimerFunc(16, update, 0); // Call the update function again after 16 milliseconds
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper z-buffering
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set the display mode
    glutInitWindowSize(800, 600); // Set the initial window size
    glutCreateWindow("Four Robot Arms"); // Create the window with the specified title

    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Set the display callback function
    glutTimerFunc(25, update, 0); // Start the update timer
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}