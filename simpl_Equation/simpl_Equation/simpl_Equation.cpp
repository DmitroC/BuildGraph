// simpl_Equation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Classes.h"
#include <chrono>
double f(double a, double b);
#define s std::chrono::steady_clock
int main()
{
	sf::RenderWindow window(sf::VideoMode(size_w[0], size_w[1]), "GIOEDjer");  //к сожалению , данный проэкт не поддерживает(пока!) скобки и корень , но мой прошлый проэкт(ссылка
	//в описании) может их воспроизводить(кроме корня)
	char t[]{ "x * x * x * x=" };
	AIO a;
	grid gr(20);
	gr.set_color(sf::Color(50, 50, 50));
	a.set(t);
	sf::Clock cl;
	a.perform(t);
	gr.set(a.diap_x(), a.diap_y());
	std::cout << cl.getElapsedTime().asSeconds();
	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::KeyPressed)
			{
				if (ev.key.code == sf::Keyboard::Up)
				{
					a.increase_x(10);
					a.increase_y(10);
					a.perform(t);
					gr.set(a.diap_x(), a.diap_y());
				}
				else if (ev.key.code == sf::Keyboard::Down)
				{
					a.increase_x(-10);
					a.increase_y(-10);
					a.perform(t);
					gr.set(a.diap_x(), a.diap_y());
				}
				else if (ev.key.code == sf::Keyboard::Z)
				{
					std::cout << "WS";
				}
			}
		}
		window.clear();
		gr.show(window);
		a.show(window);
		window.display();
	}
	return 0;
}

double f(double a, double b)
{
	return a / b * a - a;
}
