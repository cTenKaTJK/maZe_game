#define _USE_MATH_DEFINES
#include <cmath>

namespace rt {

	float distance(float player_x, float player_y, float player_angle, const char* map, const size_t map_width) {
		float distance = 0;
		for (; distance < 320; distance += 0.5) {
			float x = player_x + distance * cos(player_angle);
			float y = player_y + distance * sin(player_angle);
			if (map[int(x / SCALE) + int(y / SCALE) * map_width] != ' ')
				break;
		}
		return distance;
	}

	float wall_type(float player_x, float player_y, float player_angle, const char* map, const size_t map_width) {
		for (int distance = 0; distance < 640; distance += 2) {
			float x = player_x + distance * cos(player_angle);
			float y = player_y + distance * sin(player_angle);
			size_t cell = int(x / SCALE) + int(y / SCALE) * map_width;
			if (map[cell] != ' ') {
				if (map[cell] == 'E')
					return 2.f;
				else
					return 1.f;
			}
		}
		return 0;
	}

	float mantiss(float x, float y, float d, float angle) {
		float new_x = x + d * cos(angle);
		float new_y = y + d * sin(angle);
		float dx = (new_x / SCALE) - int((new_x / SCALE) + 0.5f);
		float dy = (new_y / SCALE) - int((new_y / SCALE) + 0.5f);
		if (abs(dy) > abs(dx)) {
			if (dy < 0) dy++;
			return dy;
		}
		if (dx < 0) dx++;
		return dx;
	}

	float** rays(float player_x, float player_y, float player_angle, const char* map, const size_t map_width) {
		float** rays = new float*[RAYS_COUNT];
		for (int i = 0; i < RAYS_COUNT; i++) {
			rays[i] = new float[3];
			float new_angle = player_angle + ((M_PI * FOV * (i - RAYS_COUNT / 2)) / (180 * RAYS_COUNT));
			rays[i][0] = distance(player_x, player_y, new_angle, map, map_width) * cos(new_angle - player_angle);
			rays[i][1] = wall_type(player_x, player_y, new_angle, map, map_width);
			rays[i][2] = mantiss(player_x, player_y, rays[i][0], new_angle);
		}
		return rays;
	}
}