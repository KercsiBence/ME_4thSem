#include "scene.h"

#include <GL/gl.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

    glBegin(GL_LINES);
    double i;
    for (i = 0; i <= 1; i+=0.2)
    {
        glVertex2f(i, 0);
        glVertex2f(i, 1);
    }
    for (i = 0; i <= 1; i+=0.2)
    {
        glVertex2f(0, i);
        glVertex2f(1, i);
    }
    
    glEnd();
    
}

