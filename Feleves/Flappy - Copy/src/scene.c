#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->map_model), "assets/models/map.obj");
	scene->map_texture = load_texture("assets/textures/map.jpg");
	load_model(&(scene->playermodel), "assets/models/bird.obj");
	load_model(&(scene->tubemodel), "assets/models/pipe.obj");
	scene->light=1.0;
    scene->map_material.ambient.red = 0.55;
    scene->map_material.ambient.green = 0.55;
    scene->map_material.ambient.blue = 0.5;
    scene->map_material.diffuse.red = 1.0;
    scene->map_material.diffuse.green = 1.0;
    scene->map_material.diffuse.blue = 1.0;
    scene->map_material.specular.red = 0.0;
    scene->map_material.specular.green = 0.0;
    scene->map_material.specular.blue = 0.0;
    scene->map_material.shininess = 0.0;
	reset_scene(scene);
}

void reset_scene(Scene* scene){
	for(int i=0; i<TUBENUMBER;i++){
		scene->tubepositions[i].z=rand()%10;
		scene->tubepositions[i].x=13+i*3.25;
		scene->tubepositions[i].y=0;
	}
}

void set_lighting(const Scene* scene)
{
    float ambient_light[] = { scene->light, scene->light, scene->light, 1.0f };
    float diffuse_light[] = { scene->light, scene->light, scene->light, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene,Camera* camera)
{
	
}

void render_scene(Scene* scene)
{
    set_material(&(scene->map_material));
    set_lighting(scene);
	glBindTexture(GL_TEXTURE_2D, scene->map_texture);
	glTranslatef(-10,-10,-3);
	glRotatef(-90,0,0,1);
	glScalef(3.0,3.0,3.0);
    draw_model(&(scene->map_model));
}

void update_player(Scene* scene,Camera* camera)
{
	
	for(int i=0;i<TUBENUMBER;i++){
		glPushMatrix();
		glTranslatef(scene->tubepositions[i].x,scene->tubepositions[i].y,scene->tubepositions[i].z);
		draw_model(&(scene->tubemodel));
		glRotatef(180,1,0,0);
		glTranslatef(0,0,-5);
		if(scene->tubepositions[i].z>5.0){
			glTranslatef(0,0,scene->tubepositions[i].z-6.5);
		}
		draw_model(&(scene->tubemodel));
		glPopMatrix();
	}
	glTranslatef(camera->position.x+3,0,camera->position.z);		
	draw_model(&(scene->playermodel));
}