#include <SFML/Graphics.hpp>
#include <string>

namespace tt {
	
	sf::Texture make_texture(std::string filename) {
		sf::Image img;
		if (img.loadFromFile(filename)) {
			sf::Texture texture;
			texture.setRepeated(true);
			if (texture.loadFromImage(img))
				return texture;
		}
	}

	sf::Text make_text(const char* label, std::string fontpath) {
		sf::Font font;
		if (font.loadFromFile(fontpath)) {
			sf::Text text(label, font);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::Black);
			text.setPosition(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT - 90);
			return text;
		}
	}

	static sf::RectangleShape make_sky() {
		sf::RectangleShape sky(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2));
		sky.setFillColor(sf::Color(150, 220, 250));
		return sky;
	}

	static sf::RectangleShape make_floor() {
		sf::RectangleShape floor(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2));
		floor.setPosition(0, WINDOW_HEIGHT / 2);
		floor.setFillColor(sf::Color(100, 80, 50));
		return floor;
	}

	sf::CircleShape make_player(float x, float y) {
		sf::CircleShape player;
		player.setPosition(x - SCALE / 4, y - SCALE / 4);
		player.setRadius(SCALE / 4);
		player.setFillColor(sf::Color::Red);
		return player;
	}
	
 }