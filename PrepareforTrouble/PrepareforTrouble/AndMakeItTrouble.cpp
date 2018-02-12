#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
using namespace std;
const int screenwidth = 1200;
const int screenheight = 800;
const int playersize = 40;
enum KEYS1 { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M};
enum KEYS2 { KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q };
enum DIRECTIONS { UP, DOWN, LEFT, RIGHT };

int main() {
	
	ALLEGRO_DISPLAY*display = NULL;
	ALLEGRO_TIMER*timer = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_BITMAP*tank = NULL;
	ALLEGRO_BITMAP*wall = NULL;
	ALLEGRO_BITMAP*dot = NULL;
	ALLEGRO_SAMPLE*bite = NULL;
	ALLEGRO_SAMPLE*win = NULL;
	ALLEGRO_SAMPLE*lose = NULL;
	ALLEGRO_SAMPLE*background = NULL;
	ALLEGRO_SAMPLE_INSTANCE*instance = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_TIMER*timer = NULL;
	ALLEGRO_FONT*font = NULL;
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
		pacman = al_create_bitmap(32, 32);
		wall = al_create_bitmap(40, 40);
		dot = al_create_bitmap(4, 4);
		al_set_target_bitmap(pacman);
		al_clear_to_color(al_map_rgb(255, 255, 0));
		al_set_target_bitmap(wall);
		al_clear_to_color(al_map_rgb(200, 200, 255));
		al_set_target_bitmap(dot);
		al_clear_to_color(al_map_rgb(255, 255, 0));
		al_set_target_bitmap(al_get_backbuffer(display));
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());


}
