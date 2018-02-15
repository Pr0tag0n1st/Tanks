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
const int screenwidth = 1200;
const int screenheight = 800;
const int playersize = 40;
enum KEYS1 { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M};
enum KEYS2 { KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q };
enum DIRECTIONS { UP, DOWN, LEFT, RIGHT };
bool Collision(int x, int y, int angle, int dir, int size, int map[120][80]);

int main() {
	bool p1keys[5]{ false, false, false, false, false };
	bool p2keys[5]{ false, false, false, false, false };
	ALLEGRO_DISPLAY*display = NULL;
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
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_TIMER*timer = NULL;
	ALLEGRO_FONT*font = NULL;

	bool doexit = false;
	int tank1_x = 60;
	int tank1_y = 60;
	int tank1_angle = 0;
	int tank2_angle = 0;
	int tank2_x = 1120;
	int tank2_y = 60;
	int tank1score = 0;
	int tank2score = 0;
	int maxscore = 10;
	int map[120][80];
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 80; j++) {
			if (i == 0 || j == 0)
				map[i][j] = 1;
			else if (i == 40 && j >= 40)
				map[i][j] = 1;
			else if (i == 55 && j <= 20)
				map[i][j] = 1;
			else if (i == 75 && j >= 60)
				map[i][j] = 1;
			else if (i == 100 && j <= 20)
				map[i][j] = 1;
			else if (i <= 20 && j == 40)
				map[i][j] = 1;
			else if (40 < i && j == 60)
				map[i][j] = 1;
			else if (i < 60 && j == 60)
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
	al_install_keyboard();
	timer = al_create_timer(.02);
	event_queue = al_create_event_queue();
	font = al_create_builtin_font();
	win = al_load_sample("Victory.wav");
	bite = al_load_sample("chomp.wav");
	background = al_load_sample("Pacman.wav");
	instance = al_create_sample_instance(background);
	al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
	al_play_sample_instance(instance);
	display = al_create_display(800, 840);
	tank1 = al_create_bitmap(32, 32);
	tank2 = al_create_bitmap(4, 4);
	wall = al_create_bitmap(40, 40);
	al_set_target_bitmap(tank1);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(tank2);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(200, 200, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	while (doexit != true && tank1score < maxscore && tank2score < maxscore) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (tank1_angle < 0)
				tank1_angle = 360;
			if (tank1_angle > 360)
				tank1_angle = 0;
			if (tank2_angle < 0)
				tank2_angle = 360;
			if (tank2_angle > 360)
				tank2_angle = 0;
			if (p1keys[KEY_UP] && !Collision(tank1_x, tank1_y, tank1_angle, UP, playersize, map)) {
			tank1_x += 4 * cos(3.14*tank1_angle / 180);
			tank1_y += 4 * sin(3.14*tank1_angle / 180);
			}
			if (p1keys[KEY_DOWN] && !Collision(tank1_x, tank1_y, tank1_angle, DOWN, playersize, map)) {
				tank1_x -= 4 * cos(3.14*tank1_angle / 180);
				tank1_y -= 4 * sin(3.14*tank1_angle / 180);
			}
			if (p1keys[KEY_LEFT])
				tank1_angle -= 1;
			if (p1keys[KEY_RIGHT])
				tank1_angle += 1;
			if (p2keys[KEY_UP] && !Collision(tank2_x, tank2_y, tank1_angle, UP, playersize, map)) {
				tank2_x += 4 * cos(3.14*tank2_angle / 180);
			}
		}


	}
}

bool Collision(int x, int y, int angle, int dir, int size, int map[120][80]) {
	int NewX;
	int NewY;
	if (dir == UP) {
		NewX = x + (4 + playersize) * cos(angle / 180);
		NewY = y + (4 + playersize) * sin(angle / 180);
	}
	else {
		NewX = x - (4 + playersize) * cos(angle / 180);
		NewY = y - (4 + playersize) * sin(angle / 180);
	}
	if (map[NewX / 10][NewY / 10] == 1)
		return 1;
	else
		return false;
}