#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <stdio.h>
#include <obj/model.h>

#define TUBENUMBER 10

typedef struct Scene
{
	Model map_model;
	Material map_material;
	GLuint map_texture;
	Model playermodel;
	Model tubemodel;
	vec3 tubepositions[TUBENUMBER];
	float light;
}Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Reset the scene.
 */

void reset_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current materials[0].
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera* camera);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);


/**
 * Update the player model.
 */

void update_player(Scene* scene,Camera* camera);

#endif /* SCENE_H */