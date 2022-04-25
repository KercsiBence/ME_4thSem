#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;
    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
	app->hud = load_texture("assets/textures/hud.png");
	app->help_panel = load_texture("assets/textures/helppanel.jpg");
	app->see_help_panel=false;
	app->camera.already_play=false;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.5, 0.8, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 100
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
			case SDL_SCANCODE_KP_PLUS:
				if(app->scene.light<1.0){
					app->scene.light+=0.02;
					glClearColor(0.5*app->scene.light, 0.8*app->scene.light, app->scene.light, 1.0);
				}
                break;
			case SDL_SCANCODE_KP_MINUS:
				if(app->scene.light>0.0){
					app->scene.light-=0.02;
					glClearColor(0.5*app->scene.light, 0.8*app->scene.light, app->scene.light, 1.0);
				}
                break;
			case SDL_SCANCODE_F1:
				if(app->see_help_panel==true){
					app->see_help_panel=false;
					break;
				}
				app->see_help_panel=true;
				break;
			case SDL_SCANCODE_SPACE:
				if(app->camera.already_play==false){
					reset_scene(&(app->scene));
					app->camera.already_play=true;
					app->camera.position.x = 0.0;
					app->camera.position.y = -2.0;
					app->camera.position.z = 2.3;
				}else{
					app->camera.velocity=0.03;
				}
				break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
	for(int i=0;i<TUBENUMBER;i++){
		if(app->scene.tubepositions[i].x<-5.0){
			if(i>0){
				app->scene.tubepositions[i].x=app->scene.tubepositions[i-1].x+3.25;
			}else{
				app->scene.tubepositions[i].x=app->scene.tubepositions[TUBENUMBER-1].x+3.25;
			}
			app->scene.tubepositions[i].z=rand()%10;
		}
		if(app->camera.already_play==true){
			app->scene.tubepositions[i].x-=elapsed_time*3;
		}
		if(app->scene.tubepositions[i].x-3<1.0 && app->scene.tubepositions[i].x-3>0){
			if(app->camera.position.z+0.3<app->scene.tubepositions[i].z || app->camera.position.z-4.7>app->scene.tubepositions[i].z){
				app->camera.already_play=false;
			}
		}
	}
    //update_scene(&(app->scene));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	set_view(&(app->camera));
	glPushMatrix();
	render_scene(&(app->scene));
	glPopMatrix();glPushMatrix();
    update_player(&(app->scene),&(app->camera));
	glPopMatrix();
	if(app->camera.already_play==false){
		render_hud(app->hud,0.0,app_height-50,app_width,app_height-50,0.0,app_height,app_width,app_height);
	}
	if(app->see_help_panel==true){
		render_hud(app->help_panel,0.0,0.0,app_width,0.0,0.0,app_height-50,app_width,app_height-50);
	}
	
    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }
    SDL_GL_SwapWindow(app->window);
}


//render_hud code made by https://github.com/SzollosiJanos with permission
void render_hud(GLuint htexture, float leftup_x,float leftup_y, float rightup_x,float rightup_y, float leftdown_x,float leftdown_y, float rightdown_x, float rightdown_y){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, app_width, app_height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,htexture);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0);	glVertex2f(leftdown_x,leftdown_y);
	glTexCoord2f(1.0,1.0);	glVertex2f(rightdown_x,rightdown_y);
	glTexCoord2f(1.0,0.0);	glVertex2f(rightup_x,rightup_y);
	glTexCoord2f(0.0,0.0);	glVertex2f(leftup_x,leftup_y);
	glEnd();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}