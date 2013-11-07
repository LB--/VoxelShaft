#include <iostream>
#include <limits>
#include <exception>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

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
	sf::RenderWindow window
	{
		sf::VideoMode(1280, 720),
		"Recipe Spelunker Alpha",
		sf::Style::Default,
		sf::ContextSettings(32)
	};
	window.setVerticalSyncEnabled(true);

	Pd p {0.0, 0.0, -7.0};
	Pd r {45.0, 45.0, 0.0};
	sf::Font arial;
	if(!arial.loadFromFile("res/arial.ttf")) return -1;
	sf::Text debug {"", arial, 12};
	debug.setPosition(10.0, 10.0);

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
						case K::Left:  r.y -= 1.0; break;
						case K::Right: r.y += 1.0; break;
						case K::Down:  r.x += 1.0; break;
						case K::Up:    r.x -= 1.0; break;
						case K::Dash:  r.z += 1.0; break;
						case K::Equal: r.z -= 1.0; break;
						case K::A: p.x -= 0.25; break;
						case K::D: p.x += 0.25; break;
						case K::S: p.y -= 0.25; break;
						case K::W: p.y += 0.25; break;
						case K::Q: p.z -= 0.5; break;
						case K::E: p.z += 0.5; break;
						case K::Return:
							p = {0.0, 0.0, -7.0};
							r = {45.0, 45.0, 0.0};
							break;
						default: break;
					}
				} break;
				default: break;
			}

			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			DrawCube(p, r, 2.0);
			
			window.pushGLStates();
			{
				std::ostringstream ds;
				ds << "p.x = " << p.x << std::endl
				   << "p.y = " << p.y << std::endl
				   << "p.z = " << p.z << std::endl
				   << "r.x = " << r.x << std::endl
				   << "r.y = " << r.y << std::endl
				   << "r.z = " << r.z << std::endl;
				debug.setString(ds.str());
				window.draw(debug);
			}
			window.popGLStates();

			window.display();
		}
	}();}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
