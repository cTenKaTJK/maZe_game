#define _USE_MATH_DEFINES
#define SCALE 20
#define FOV 90
#define RAYS_COUNT 1024
#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024
#define TEXTURE_SIZE 64
#define STEP 0.5
#define ANGLE 0.05


#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <cmath>
#include "map.hpp"
#include "ray.hpp"
#include "texturing.hpp"


int main() {
	
	bool map_enabled = true;

	mt::Map m("src/levels/level1.txt");
	const size_t map_width = m.width();
	const char* map = m.get();
	auto map_img = m.map_draw();

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "testo-presto", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	auto wall_texture = tt::make_texture("src/textures/brick.png");
	auto exit_texture = tt::make_texture("src/textures/ext.png");
	auto exit_text = tt::make_text("press [SPACE] to escape", "src/fonts/font.ttf");

	float player_x = SCALE * 1.5;
	float player_y = SCALE * 1.5;
	float player_angle = 0;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break; }
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			player_angle -= ANGLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			player_angle += ANGLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (rt::distance(player_x, player_y, player_angle, map, map_width) > 2) {
				player_x += cos(player_angle) * STEP;
				player_y += sin(player_angle) * STEP;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (rt::distance(player_x, player_y, player_angle + M_PI, map, map_width) > 2) {
				player_x += cos(player_angle + M_PI) * STEP;
				player_y += sin(player_angle + M_PI) * STEP;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (rt::distance(player_x, player_y, player_angle - (M_PI / 2), map, map_width) > 2) {
				player_x += cos(player_angle - (M_PI / 2)) * STEP;
				player_y += sin(player_angle - (M_PI / 2)) * STEP;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (rt::distance(player_x, player_y, player_angle + (M_PI / 2), map, map_width) > 2) {
				player_x += cos(player_angle + (M_PI / 2)) * STEP;
				player_y += sin(player_angle + (M_PI / 2)) * STEP;
			}
		}

		window.draw(tt::make_sky());
		window.draw(tt::make_floor());

		auto rays_arr = rt::rays(player_x, player_y, player_angle, map, map_width);
		for (int i = 0; i < RAYS_COUNT; i++) {
			sf::Sprite wall_sprite;
			float texture_column = rays_arr[i][2] * TEXTURE_SIZE;

			if (rays_arr[i][1] == 2.f) wall_sprite.setTexture(exit_texture);
			else wall_sprite.setTexture(wall_texture);

			wall_sprite.setTextureRect(sf::IntRect(
				texture_column,
				0,
				WINDOW_WIDTH / RAYS_COUNT,
				TEXTURE_SIZE));

			wall_sprite.setScale(sf::Vector2f(1.f,
				SCALE * WINDOW_HEIGHT / rays_arr[i][0] / TEXTURE_SIZE));

			wall_sprite.setPosition(sf::Vector2f(
				(WINDOW_WIDTH / RAYS_COUNT) * i,
				(WINDOW_HEIGHT / 2) - (SCALE * WINDOW_HEIGHT / rays_arr[i][0] / 2)));

			window.draw(wall_sprite);
		}
		
		if (map_enabled) {
			for (size_t map_rect = 0; map_rect < map_img.size(); map_rect++)
				window.draw(map_img[map_rect]);
			window.draw(tt::make_player(player_x, player_y));
		}

		//if (rt::wall_type(player_x, player_y, player_angle, map, map_width) == 2 &&
			//rt::distance(player_x, player_y, player_angle, map, map_width) < 20)
			//window.draw(exit_text);

		window.display();
		window.clear();

	}
	return 0;
}
