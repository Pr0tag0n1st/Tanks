#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
using namespace std;
const int screenwidth = 1200;
const int screenhieght = 800;
const int playersize = 40;
enum KEYS1 { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M};
enum KEYS2 { KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q };
enum DIRECTIONS { UP, DOWN, LEFT, RIGHT };

int main() {
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
		system("Pause");
		ALLEGRO_DISPLAY* display = al_create_display(screenwidth, screenhieght);


}
