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
	
	double rx = 45.0
	,      ry = 45.0
	,      rz = 0.0;

	try
	{[&]{
		struct Resources
		{
			Resources()
			{
				glShadeModel(GL_SMOOTH);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
				resize(1280, 720);
			}
			void resize(GLsizei x, GLsizei y)
			{
				glViewport(0, 0, x, y);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				
				gluPerspective(45.0, static_cast<GLdouble>(x)/y, 0.1, 100.0);
				
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
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
					res.resize(e.size.width, e.size.height);
				} break;
				case sf::Event::KeyPressed:
				{
					using K = sf::Keyboard::Key;
					switch(e.key.code)
					{
						case K::Left:  rx -= 1.0; break;
						case K::Right: rx += 1.0; break;
						case K::Down:  ry -= 1.0; break;
						case K::Up:    ry += 1.0; break;
						case K::Dash:  rz -= 1.0; break;
						case K::Equal: rz += 1.0; break;
						case K::Return: rx = ry = 45.0; rz = 0.0; break;
						default: break;
					}
				} break;
				default: break;
			}

			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			DrawCube({0.0, 0.0, -7.0}, {rx, ry, rz}, 2.0);

			window.display();
		}
	}();}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
