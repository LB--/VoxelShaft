#include <iostream>
#include <limits>
#include <exception>
#include <sstream>
#include <cmath>

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
	//glLoadIdentity();
	glPushMatrix();
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
	glPopMatrix();
}

void CenterMouse(sf::Window &w)
{
	sf::Mouse::setPosition(sf::Vector2i(w.getSize()/2u), w);
}

double rad(double deg)
{
	return deg/180.0*3.1415926;
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

	Pd const p_init {2.0, -4.0, -7.0}
	,        r_init {30, 5.0, 0.0};
	Pd p = p_init
	,  r = r_init;
	sf::Font arial;
	if(!arial.loadFromFile("res/arial.ttf")) return -1;
	sf::Text debug {"", arial, 12};
	debug.setPosition(10.0, 10.0);
	bool focus = false;
	double cam_speed = 0.25;

	try
	{[&]{
		struct Resources
		{
			Resources(sf::RenderWindow &w)
			{
				glShadeModel(GL_SMOOTH);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
				resize(w.getSize().x, w.getSize().y);
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
		} res(window);
		for(;;)
		{
			sf::Event e;
			while(window.pollEvent(e)) switch(e.type)
			{
				using E = sf::Event;
				case E::Closed:
				{
					return;
				} break;
				case E::Resized:
				{
					res.resize(e.size.width, e.size.height);
				} break;
				case E::KeyPressed:
				{
					using K = sf::Keyboard::Key;
					switch(e.key.code)
					{
						case K::Left:  r.z += 1.0; break;
						case K::Right: r.z -= 1.0; break;
						case K::Return:
						{
							p = p_init;
							r = r_init;
						} break;
						default: break;
					}
				} break;
				case E::MouseButtonPressed:
				{
					switch(e.mouseButton.button)
					{
						case sf::Mouse::Button::Left:
						{
							CenterMouse(window);
						} break;
						default: break;
					}
				}
				case E::GainedFocus:
				{
					focus = true;
				} break;
				case E::LostFocus:
				{
					focus = false;
				} break;
				default: break;
			}
			if(focus)
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					auto off = sf::Mouse::getPosition(window) - sf::Vector2i(window.getSize()/2u);
					r.x += off.y/2.0;
					r.y += off.x/2.0;
					CenterMouse(window);
				}

				using K = sf::Keyboard::Key;
				if(sf::Keyboard::isKeyPressed(K::A)) //Left
				{
					p.x += cam_speed*std::cos(rad(r.y));
					p.z += cam_speed*std::sin(rad(r.y));
				}
				if(sf::Keyboard::isKeyPressed(K::D)) //Right
				{
					p.x -= cam_speed*std::cos(rad(r.y));
					p.z -= cam_speed*std::sin(rad(r.y));
				}
				if(sf::Keyboard::isKeyPressed(K::S)) //Backward
				{
					p.x += cam_speed*std::sin(rad(r.y))*std::cos(rad(r.x));
					p.y -= cam_speed*std::sin(rad(r.x));
					p.z -= cam_speed*std::cos(rad(r.y))*std::cos(rad(r.x));
				}
				if(sf::Keyboard::isKeyPressed(K::W)) //Forward
				{
					p.x -= cam_speed*std::sin(rad(r.y))*std::cos(rad(r.x));
					p.y += cam_speed*std::sin(rad(r.x));
					p.z += cam_speed*std::cos(rad(r.y))*std::cos(rad(r.x));
				}
				if(sf::Keyboard::isKeyPressed(K::Space)) //Up
				{
					p.x -= cam_speed*std::sin(rad(r.y))*std::sin(rad(r.x));
					p.y -= cam_speed*std::cos(rad(r.x));
					p.z += cam_speed*std::cos(rad(r.y))*std::sin(rad(r.x));
				}
				if(sf::Keyboard::isKeyPressed(K::LShift)) //Down
				{
					p.x += cam_speed*std::sin(rad(r.y))*std::sin(rad(r.x));
					p.y += cam_speed*std::cos(rad(r.x));
					p.z -= cam_speed*std::cos(rad(r.y))*std::sin(rad(r.x));
				}
			}

			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			glRotated(r.x, 1.0, 0.0, 0.0);
			glRotated(r.y, 0.0, 1.0, 0.0);
			glRotated(r.z, 0.0, 0.0, 1.0);
			glTranslated(p.x, p.y, p.z);

			glPushMatrix();
				DrawCube({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2.0);
				DrawCube({-2.5, 0.0, 0.0}, {10.0, -20.0, 0.0}, 2.0);
			glPopMatrix();

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
