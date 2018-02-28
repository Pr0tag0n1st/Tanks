#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
using namespace std;
const int SCREEN_W = 1200;
const int SCREEN_H = 800;
enum KEYS1 { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M};
enum KEYS2 { KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q };
enum DIRECTIONS { UP, DOWN, LEFT, RIGHT };
bool Collision(int x, int y, int angle, int dir, int size, int map[120][80]);

int main() {

	
	bool p1keys[5]{ false, false, false, false, false };
	bool p2keys[5]{ false, false, false, false, false };
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER*timer = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_BITMAP*tank1 = NULL;
	ALLEGRO_BITMAP*wall = NULL;
	ALLEGRO_BITMAP*tank2 = NULL;
	ALLEGRO_SAMPLE*bite = NULL;
	ALLEGRO_SAMPLE*win = NULL;
	ALLEGRO_SAMPLE*lose = NULL;
	ALLEGRO_SAMPLE*background = NULL;
	ALLEGRO_SAMPLE_INSTANCE*instance = NULL;
	ALLEGRO_FONT*font = NULL;

	bool doexit = false;
	bool redraw;
	int tanksize = 40;
	int wallsize = 10;
	int movespeed = 4;
	int tank1_x = 60;
	int tank1_y = 60;
	int tank1_angle = 0;
	int tank2_angle = 0;
	int tank2_x = 1120;
	int tank2_y = 60;
	int tank1score = 0;
	int tank2score = 0;
	int maxscore = 10;
	int dir1=1;
	int dir2=1;

	int map[120][80];
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 80; j++) {
			if (i == 0 || j == 0)
				map[i][j] = 1;
			else if (i == 40 && j >= 40)
				map[i][j] = 1;
			else if (i == 50 && j <= 20)
				map[i][j] = 1;
			else if (i == 70 && j >= 60)
				map[i][j] = 1;
			else if (i == 100 && j <= 20)
				map[i][j] = 1;
			else if (40 < i && j == 60)
				map[i][j] = 1;

			else if (80 < i && j == 40)
				map[i][j] = 1;
			else if (i < 90 && j == 40)
				map[i][j] = 1;
			else if (105 < i && j == 40)
				map[i][j] = 1;
			else if (i < 120 && j == 40)
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
	}
	for (int i = 0; i < 120; i++)
		for (int j = 0; j < 80; j++)
			cout << map[i][j];
	//initializing allegro
	al_init();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	//initializing variables
	display = al_create_display(SCREEN_W, SCREEN_H);
	tank1 = al_create_bitmap(tanksize, tanksize);
	tank2 = al_create_bitmap(tanksize, tanksize);
	wall = al_create_bitmap(wallsize, wallsize);
	event_queue = al_create_event_queue();
	font = al_load_ttf_font("pepperoni_pizza.ttf", 48, 0);
	//coloring bitmaps
	al_set_target_bitmap(tank1);
	al_clear_to_color(al_map_rgb(0, 255, 0));
	al_set_target_bitmap(tank2);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(200, 200, 255));
//	instance = al_create_sample_instance(background);
//	al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
//	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
//	al_play_sample_instance(instance);
	cout << "flag 1";
	timer = al_create_timer(.02);
	//initializing event sources
	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	cout << "flag bip";

	//game loop
	while (doexit != true && tank1score < maxscore && tank2score < maxscore) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//timer/movement section
		if (ev.type == ALLEGRO_EVENT_TIMER) { //Movement section
			if (tank1_angle < 0)
				tank1_angle = 360;
			if (tank1_angle > 360)
				tank1_angle = 0;
			if (tank2_angle < 0)
				tank2_angle = 360;
			if (tank2_angle > 360)
				tank2_angle = 0;
			if (p1keys[KEY_UP] && !Collision(tank1_x, tank1_y, tank1_angle, UP, tanksize, map)) {
				tank1_x += movespeed * cos(3.14*tank1_angle / 180);
				tank1_y += movespeed * sin(3.14*tank1_angle / 180);
				dir1 = 0;
			}
			if (p1keys[KEY_DOWN] && !Collision(tank1_x, tank1_y, tank1_angle, DOWN, tanksize, map)) {
				tank1_x -= movespeed * cos(3.14*tank1_angle / 180);
				tank1_y -= movespeed * sin(3.14*tank1_angle / 180);
				dir1 = 1;
			}
			if (p1keys[KEY_LEFT]) {
				tank1_angle -= 2;
				dir1 = 2;
			}
			if (p1keys[KEY_RIGHT]) {
				tank1_angle += 2;
				dir1 = 3;
			}
			if (p2keys[KEY_UP] && !Collision(tank2_x, tank2_y, tank2_angle, UP, tanksize, map)) {
				tank2_x += movespeed * cos(3.14*tank2_angle / 180);
				tank2_y += movespeed * sin(3.14*tank2_angle / 180);
				dir2 = 0;
			}
			if (p2keys[KEY_DOWN] && !Collision(tank2_x, tank2_y, tank2_angle, DOWN, tanksize, map)) {
				tank2_x -= movespeed * cos(3.14*tank2_angle / 180);
				tank2_y -= movespeed * sin(3.14*tank2_angle / 180);
				dir2 = 1;
			}
			if (p2keys[KEY_LEFT]) {
				tank2_angle -= 2;
				dir2 = 2;
			}
			if (p2keys[KEY_RIGHT]) {
				tank2_angle += 2;
				dir2 = 3;
			}
		
			redraw = true;

		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//key press algorithm		
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				p1keys[0] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				p1keys[1] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				p1keys[2] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				p1keys[3] = true;
				break;
			case ALLEGRO_KEY_M:
				p1keys[4] = true;
				break;
			case ALLEGRO_KEY_W:
				p2keys[0] = true;
				break;
			case ALLEGRO_KEY_S:
				p2keys[1] = true;
				break;
			case ALLEGRO_KEY_A:
				p2keys[2] = true;
				break;
			case ALLEGRO_KEY_D:
				p2keys[3] = true;
				break;
			case ALLEGRO_KEY_Q:
				p2keys[4] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				p1keys[0] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				p1keys[1] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				p1keys[2] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				p1keys[3] = false;
				break;
			case ALLEGRO_KEY_M:
				p1keys[4] = false;
				break;
			case ALLEGRO_KEY_W:
				p2keys[0] = false;
				break;
			case ALLEGRO_KEY_S:
				p2keys[1] = false;
				break;
			case ALLEGRO_KEY_A:
				p2keys[2] = false;
				break;
			case ALLEGRO_KEY_D:
				p2keys[3] = false;
				break;
			case ALLEGRO_KEY_Q:
				p2keys[4] = false;
				break;
			}
		}
		//render section
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old square dissapears
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			for (int i = 0; i < 120; i++)
				for (int j = 0; j < 80; j++)
					if (map[i][j] == 1)
						al_draw_bitmap(wall, i * wallsize, j * wallsize, 0);

			al_draw_rotated_bitmap(tank1, tanksize / 2, tanksize / 2, tank1_x, tank1_y, ((tank1_angle*3.14)/180), 0);
			al_draw_rotated_bitmap(tank2, tanksize / 2, tanksize / 2, tank2_x, tank2_y, ((tank2_angle*3.14)/180), 0);
			al_flip_display();

		}

	}
	al_destroy_bitmap(tank1);
	al_destroy_bitmap(tank2);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
bool Collision(int x, int y, int angle, int dir, int size, int map[120][80]) {
	int NewX;
	int NewY;
	if (dir == UP) {
		NewX = x + (4 + size) * cos(angle / 180);
		NewY = y + (4 + size) * sin(angle / 180);
	}
	else {
		NewX = x - (4 + size) * cos(angle / 180);
		NewY = y - (4 + size) * sin(angle / 180);
	}
	if (map[NewX / 10][NewY / 10] == 1)
		return true;
	else
		return false;
}