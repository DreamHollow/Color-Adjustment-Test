#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Display
{
public:
	Display();
	virtual ~Display();

	// Public Functions
	void run();

	// Public Objects
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(); // Just a window that removes itself from memory after it runs

private:
	// Variables
	int v_width;
	int v_height;
	int v_bits;
	float rate;
	float dt; // Delta Time

	// Color Unique
	// Left Lines
	int l_red = 255;
	int l_green = 255;
	int l_blue = 255;

	// Right Lines
	int r_red = 255;
	int r_green = 255;
	int r_blue = 255;

	// Functions
	void init_variables();
	void init_window();
	int create_display();
	void init_lines();
	void clear_lines();
	void set_colors();

	// Window Control
	void polling_events();
	void update();
	void update_lines();
	void update_input();
	void render();
	void render_lines();

	// Time
	void update_dt();
	sf::Clock clock;

	// Objects
	sf::VideoMode vid_mode;
	sf::Event window_event;
	sf::RectangleShape line;
	std::vector<sf::RectangleShape> lines;
	sf::Color left_color;
	sf::Color right_color;
};

#endif
