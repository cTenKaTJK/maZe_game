#include <string>
#include <fstream>


namespace mt {
	class Map {
	private:
		size_t map_height_;
		size_t map_width_;
		char* map_buf;

	public:
		Map(const std::string& filename) {
			map_buf = new char[512];
			std::ifstream in(filename);
			std::string line;
			size_t height = 0;
			static size_t width = 0;
			if (in.is_open()) {
				while (std::getline(in, line)) {
					size_t len = line.length();
					width = len;
					for (size_t i = 0; i < len + 1; i++)
						map_buf[height * width + i] = line[i];
					for (size_t j = 0; j < (width - len); j++)
						map_buf[height * width + len + j] = ' ';
					height++;
				}
			}
			in.close();

			map_height_ = height;
			map_width_ = width;
		}

		~Map() { if(map_buf) delete[] map_buf; }

		char* get() { return map_buf; }

		size_t height() { return map_height_; }

		size_t width() { return map_width_; }
		
		std::vector<sf::RectangleShape> map_draw() {
			std::vector<sf::RectangleShape> map_img;
			for (size_t map_row = 0; map_row < map_height_; map_row++)
			{
				for (size_t map_col = 0; map_col < map_width_; map_col++)
				{
					if (map_buf[map_row * map_width_ + map_col] != ' ')
					{
						sf::RectangleShape rectangle(sf::Vector2f(SCALE, SCALE));
						rectangle.setPosition(map_col * SCALE, map_row * SCALE);

						if (map_buf[map_row * map_width_ + map_col] == 'E')
							rectangle.setFillColor(sf::Color::Blue);
						else
							rectangle.setFillColor(sf::Color::White);
						map_img.push_back(rectangle);
					}
				}
			}
			return map_img;
		}
	};
}