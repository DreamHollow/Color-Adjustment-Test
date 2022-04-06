#include "Display.hpp"

Display::Display()
{
	this->init_variables();
	this->init_window();
	this->create_display();
	this->init_lines();
};

Display::~Display()
{
	this->clear_lines(); // Do this first to prevent memory issues

	std::cout << "Lines vector capacity is now " << lines.size() << " size.\n";
};

void Display::init_variables()
{
	std::cout << "Initializing setup...\n";

	this->dt = 0;
	this->rate = 1;
	this->v_width = 800;
	this->v_height = 600;
	this->v_bits = 32;
	this->left_color = sf::Color::White;
	this->right_color = sf::Color::White;

	std::cout << "Initialization complete.\n";
};

void Display::init_window()
{
	std::cout << "Beginning window configurations...\n";

	this->vid_mode.width = v_width;
	this->vid_mode.height = v_height;
	this->vid_mode.bitsPerPixel = v_bits;

	std::cout << "Configuration complete.\n";
};

int Display::create_display()
{
	if (this->vid_mode.isValid())
	{
		std::cout << "Creating render window...\n";

		this->window->create(vid_mode, "SFML Line Test", sf::Style::Close);
		this->window->setFramerateLimit(60);

		std::cout << "Render window created.\n";
	}
	else
	{
		std::cout << "A render window could not be created due to misconfiguration.\n";

		return 1;
	}

	return 0;
};

void Display::init_lines()
{
	float j = 0;

	std::cout << "Emplacing line objects...\n";

	line.setPosition(sf::Vector2f(0.f, 0.f));
	line.setFillColor(sf::Color::White);
	line.setSize(sf::Vector2f(1.f, 800.f));
	line.setScale(1.f, 1.f);

	this->lines.emplace_back(line); // Emplace first line

	for (int i = 1; i < 800; i++) // Start one positional placement ahead
	{
		j = static_cast<float>(i);

		line.setPosition(sf::Vector2f(j, 0.f));
		this->lines.emplace_back(line);
	}

	std::cout << "Line objects emplaced.\n";
};

void Display::clear_lines()
{
	this->lines.clear();
	this->lines.shrink_to_fit();
};

void Display::set_colors()
{
	sf::Vector2f left_vector{ 399.f, 0.f };
	sf::Vector2f right_vector{ 401.f, 0.f };
	
	for (auto i = lines.begin(); i != lines.end(); i++)
	{
		if (i->getPosition().x < left_vector.x)
		{
			i->setFillColor(left_color);
		}
		else if (i->getPosition().x > right_vector.x)
		{
			i->setFillColor(right_color);
		}
	}
};

void Display::polling_events()
{
	while (this->window->pollEvent(this->window_event))
	{
		switch (this->window_event.type)
		{
		case sf::Event::Closed:
			std::cout << "Window was closed by user.\n";
			this->window->close();
			break;
		}
	}
};

void Display::update()
{
	this->update_dt();
	this->polling_events();
	this->update_input();
	this->set_colors();
	this->update_lines();
};

void Display::update_lines()
{
	for (auto a : lines)
	{
		a.getFillColor();
		a.getPosition();
		a.getSize();
		a.getScale();
	}
};

void Display::update_input()
{
	rate = rate + dt;

	// If rate meets or exceeds the threshold, the input is registered
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (rate > 0.5) // If half a second has passed
		{
			if (l_green > 0 && l_blue > 0)
			{
				std::cout << "Adjusting color: LEFT\n";

				l_green -= 1;
				l_blue -= 1;
			}
			else
			{
				std::cout << "ERROR: LEFT COLOR PEAK\n";
			}

			this->left_color.r = l_red;
			this->left_color.g = l_green;
			this->left_color.b = l_blue;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (rate > 0.5)
		{
			if (r_red > 0 && r_green > 0)
			{
				std::cout << "Adjusting color: RIGHT\n";

				r_red -= 1;
				r_green -= 1;
			}
			else
			{
				std::cout << "ERROR: RIGHT COLOR PEAK\n";
			}

			this->right_color.r = r_red;
			this->right_color.g = r_green;
			this->right_color.b = r_blue;
		}
	}
	else
	{
		rate = 0; // Resets
	}
};

void Display::render()
{
	this->window->clear();

	// Render items
	this->render_lines();

	this->window->display();
};

void Display::render_lines()
{
	for (auto it : lines)
	{
		this->window->draw(it); // Draw the pointer, not the stack object
	}
}
void Display::update_dt()
{
	this->dt = clock.restart().asSeconds();
};

void Display::graphics()
{
	this->update();
	this->render();
};
