#include <iostream>
#include <limits>
#include <exception>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

struct Pf
{
	GLfloat x, y, z;
};
struct Pd
{
	GLdouble x, y, z;
};

void DrawCube(Pd p, Pd r, GLdouble size)
{
	glLoadIdentity();
	glTranslated(p.x, p.y, p.z);
	glRotated(r.x, 1.0, 0.0, 0.0);
	glRotated(r.y, 0.0, 1.0, 0.0);
	glRotated(r.z, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	{
		size /= 2.0;

		glColor3d(1.0, 0.0, 0.0); //red
		glVertex3d(+size, +size, -size);
		glVertex3d(-size, +size, -size);
		glVertex3d(-size, +size, +size);
		glVertex3d(+size, +size, +size);

		glColor3d(0.0, 1.0, 0.0); //green
		glVertex3d(+size, -size, +size);
		glVertex3d(-size, -size, +size);
		glVertex3d(-size, -size, -size);
		glVertex3d(+size, -size, -size);

		glColor3d(0.0, 0.0, 1.0); //blue
		glVertex3d(+size, +size, +size);
		glVertex3d(-size, +size, +size);
		glVertex3d(-size, -size, +size);
		glVertex3d(+size, -size, +size);

		glColor3d(1.0, 1.0, 0.0); //yellow
		glVertex3d(+size, -size, -size);
		glVertex3d(-size, -size, -size);
		glVertex3d(-size, +size, -size);
		glVertex3d(+size, +size, -size);

		glColor3d(1.0, 0.0, 1.0); //pink
		glVertex3d(-size, +size, +size);
		glVertex3d(-size, +size, -size);
		glVertex3d(-size, -size, -size);
		glVertex3d(-size, -size, +size);

		glColor3d(0.0, 1.0, 1.0); //cyan
		glVertex3d(+size, +size, -size);
		glVertex3d(+size, +size, +size);
		glVertex3d(+size, -size, +size);
		glVertex3d(+size, -size, -size);
	}
	glEnd();
}

int main(int nargs, char const *const *args)
{
	sf::Window window
	{
		sf::VideoMode(1280, 720),
		"Recipe Spelunker Alpha",
		sf::Style::Default,
		sf::ContextSettings(32)
	};
	window.setVerticalSyncEnabled(true);

	try
	{[&]{
		struct Resources
		{
			Resources()
			{
				//
			}
			~Resources()
			{
				//
			}
		} res;
		for(;;)
		{
			sf::Event e;
			while(window.pollEvent(e)) switch(e.type)
			{
				case sf::Event::Closed:
				{
					return;
				} break;
				case sf::Event::Resized:
				{
					glViewport(0, 0, e.size.width, e.size.height);
				} break;
				default: break;
			}

			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			DrawCube({1.5, 0.0, -7.0}, {1.0, 1.0, 1.0}, 2.0);

			window.display();
		}
	}();}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
