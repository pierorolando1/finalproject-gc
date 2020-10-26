#include "../utils.h"
#include <math.h>

/**
 * Method to return the rgb normalized color vector 
 * 
 * @param R the red color value [0, 255]
 * @param G the red color value [0, 255]
 * @param B the red color value [0, 255]
 */
float* getColor(int R, int G, int B) {
    return new float[3] { R/255.f, G/255.f, B/255.f };
}

/**
 * Function to draw a crosshair to help user localization
 * 
 * Source? https://guidedhacking.com/threads/opengl-draw-a-crosshair.6588/
 */
void drawCrosshair(int windowsWidth, int windowsHeight) {
    glPushMatrix();
    glViewport(0, 0, windowsWidth, windowsHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowsWidth, windowsHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(240, 240, 240);//white
    glLineWidth(2.0);

    int crossHair[8] =
    {
    windowsWidth / 2 - 7, windowsHeight / 2, // horizontal line
    windowsWidth / 2 + 7, windowsHeight / 2,

    windowsWidth / 2, windowsHeight / 2 + 7, //vertical line
    windowsWidth / 2, windowsHeight / 2 - 7
    };

    // activate vertext array state and assign pointer to vertext array data
    glEnableClientState(GL_VERTEX_ARRAY);

    //2 = number of coordinates per vertext we are doing 2d so I don't need the Z coordinate
    // GL_INT = data type held in array
    // crossHair = pointer to vertext data array


    glVertexPointer(2, GL_INT, 0, crossHair);

    //draw primitive GL_LINES starting at the first vertex, use 2 total vertices
    glDrawArrays(GL_LINES, 0, 2); //draw horizontal line
    //Same as above but start at second vertex
    glDrawArrays(GL_LINES, 2, 2); //draw vertical line

    // deactivate vertex array state after drawing
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void drawAxis(bool drawXAxis, bool drawYAxis, bool drawZAxis) {

    glPushMatrix();
    
    if (drawXAxis) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(5, 0, 0);
        glEnd();
    }

    if (drawYAxis) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 5, 0);
        glEnd();
    }

    if (drawZAxis) {
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 5);
        glEnd();
    }

    glPopMatrix();
}

/**
 * Method to return the position at the surface of a sphere
 * 
 * @param x0 a float that represents the initial x position
 * @param y0 a float that represents the initial y position
 * @param z0 a float that represents the initial z position
 * @param radius a float that represents the sphere radius
 * @param xAngle a float that represents the horizontal angle variation, i.e (alpha)
 * @param yAngle a float that represents the vertical angle variation, i.e (phi)
 * */
std::vector<float> getSpherePositions(float x0, float y0, float z0, float radius, float xAngle, float yAngle) {
    float x = x0 + radius * cos(xAngle) * sin(yAngle);
    float y = y0 + radius * cos(yAngle);
    float z = z0 + radius * sin(xAngle) * sin(yAngle);

    std::vector<float> result { x, y, z };
    return result;
}