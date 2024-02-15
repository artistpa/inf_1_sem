#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <set>
#include <iostream>

using namespace sf;

const double PI = 3.1415926536;
const double coef = 1;
const int boundX = 1200;
const int boundY = 800;
const float sunMass = 1000;
const float radiusCoef = 0.1;

struct Body
{
	float x;
	float y;
	float vx;
	float vy;
	float m;
	float r = m * radiusCoef;
};
struct centre
{
	float x;
	float y;
	int r = 5;
};
//std::vector<Body> bodies = { Body{500.0, 300.0, 0.0, 0.0, 100.0}, Body{400.0, 300.0, 0.0, 1.0, 100.0}, Body{600.0, 300.0, 0.0, -1, 100.0}};
std::vector<Body> bodies = { Body{450.0, 300.0, 1.0, 0.5773502692, 100.0}, Body{550.0, 300.0, -1.0, 0.5773502692, 100.0}, Body{500.0, 386.6025403784, 0.0, -1, 100.0}};
void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::vector<Body> handleEvents(RenderWindow* window) {
	std::vector<Body> newBodies;
	Event event;

	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();
		if (event.type == Event::MouseButtonPressed)
		{
			sf::Vector2i position = sf::Mouse::getPosition(*window);
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				newBodies.push_back(Body{ static_cast<float>(position.x), static_cast<float>(position.y), 3.0, 0.0, 100.0});
			}
			else 
			{
				newBodies.push_back(Body{
						static_cast<float>(position.x),
						static_cast<float>(position.y),
					0.0, 0.0, 100.0});
			}
		}
	}

	return newBodies;
}

CircleShape renderBody(Body& b)
{
	b.r = b.m * radiusCoef;
	CircleShape circle(b.r);
	circle.setOrigin(b.r, b.r);
	circle.setPosition(b.x, b.y);
	if (b.m >= sunMass)
	{
		circle.setFillColor(Color(246, 222, 1));
	}
	return circle;
}
CircleShape renderCentre(centre& c)
{
        CircleShape circle(c.r);
        circle.setOrigin(c.r, c.r);
        circle.setPosition(c.x, c.y);
        return circle;
}

void update(RenderWindow* window)
{
	std::set<int> deleteBodies;
	int size = bodies.size();
	centre c;
	float summ, sumx, sumy;
	for (int i = 0; i < size; i++)
	{
		Body& p0 = bodies[i];
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;

			Body& p = bodies[j];
			double d = sqrt(pow(p0.x - p.x, 2) + pow(p0.y - p.y, 2));
			if (d > p0.r + p.r)
			{
				p0.vx += coef * p.m / d / d * (p.x - p0.x) / d;
				p0.vy += coef * p.m / d / d * (p.y - p0.y) / d;
			}
			else {
				if (p0.m >= sunMass && p.m >= sunMass)
				{
					deleteBodies.insert(i);
					deleteBodies.insert(j);
				}
				else
				{
					if (p0.m < sunMass)
					{
						deleteBodies.insert(i);
					}
					else {
						p0.m += p.m * 0.1;
					}

					if (p.m < sunMass)
					{
						deleteBodies.insert(j);
					}
					else {
						p.m += p0.m * 0.1;
					}
				}
			}
		}
		p0.x += p0.vx;
		p0.y += p0.vy;

		for (int i = 0; i < size; i++){
			sumx += bodies[i].m * bodies[i].x;
			sumy += bodies[i].m * bodies[i].y;
			summ += bodies[i].m;
		}
		
		c.x = sumx / summ;
		c.y = sumy / summ;

		CircleShape circle = renderBody(p0);
		CircleShape circle1 = renderCentre(c);
		window->draw(circle);
		window->draw(circle1);
		
		std::cout <<  c.x << '\t' << c.y << std::endl;
	}

	//std::vector<Body> copy_bodies;

	//for (int i = 0; i < bodies.size(); ++i)
	//{
	//	if (deleteBodies.find(i) == deleteBodies.end())
	//	{
	//		copy_bodies.push_back(bodies[i]);
	//	}
	//}

	//bodies = copy_bodies;
}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8.0;
	RenderWindow window(VideoMode(boundX, boundY), "Planet Simulator", sf::Style::Close, settings);

	int sleep_time = 50;

	while (window.isOpen())
	{
		std::vector<Body> bodiesToAdd = handleEvents(&window);

		window.clear(Color(0, 0, 0, 0));
		update(&window);
		bodies.insert(bodies.end(), bodiesToAdd.begin(), bodiesToAdd.end());
		bodiesToAdd.clear();

		window.display();

		sleep(sleep_time);
	}

	return 0;
}
