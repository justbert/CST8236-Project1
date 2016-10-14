#include "Windmill.h"
#include <SFML/Audio.hpp>

int main(int argc, char *argv)
{
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Windmills", sf::Style::Titlebar | sf::Style::Close);

  //Speeds
  float vaneSpeed = 75.0f;
  float windmillSpeed = 80.0f;
  float bgSpeed = 30.0f;

  //background
  sf::Texture cloudsTexture;
  cloudsTexture.loadFromFile("res/tileable-cloud-patterns-1.jpg");
  cloudsTexture.setRepeated(true);

  sf::RectangleShape background;
  background.setTexture(&cloudsTexture);
  background.setSize(sf::Vector2f(1024.0f * 5, 1024.0f));
  
  sf::Vector2f windmill1InitialPosition(window.getSize().x *0.20, window.getSize().y / 2);
  sf::Vector2f windmill2RelativePosition(window.getSize().x *0.30, 0.0f);
  sf::Vector2f windmill3RelativePosition(window.getSize().x *0.30, 0.0f);

  sf::Vector2f windmill2GlobalPosition(window.getSize().x *0.50, window.getSize().y / 2);
  sf::Vector2f windmill3GlobalPosition(window.getSize().x *0.80, window.getSize().y / 2);

  sf::Vector2f windmill2Origin(-(window.getSize().x *0.30), 0.0f);
  sf::Vector2f windmill3Origin(-(window.getSize().x *0.30), 0.0f);
  sf::Vector2f windmill1Origin(window.getSize().x *0.35, window.getSize().y / 2);

  sf::Vector2f windmill2SoloOrigin(window.getSize().x *0.20, 150.0f);
  sf::Vector2f windmill3SoloOrigin(window.getSize().x *0.50, 150.0f);

  //Audio
  sf::SoundBuffer buffer;
  buffer.loadFromFile("res/wind-gust-01.wav");
  sf::Sound sound(buffer);
  sound.setLoop(true);
  sound.play();

  //Switches
  int mouseY = 0;
  int mouseX = 0;
  bool mouseYMoved = false;
  bool mouseXMoved = false;
  
  enum windmillSelected { left=1, middle, right, all};
  windmillSelected selected = left;

  Windmill windmill1 = Windmill();
  Windmill windmill2 = Windmill();
  Windmill windmill3 = Windmill();

  //Initial setup
  windmill1.setPosition(windmill1InitialPosition);
  windmill2.setPosition(windmill2GlobalPosition);
  windmill3.setPosition(windmill3GlobalPosition);

  windmill1.SetOrigin(windmill1Origin);
  windmill2.SetOrigin(windmill2SoloOrigin);
  windmill3.SetOrigin(windmill3SoloOrigin);
 

  sf::Event evt;
  sf::Clock appTimer;
  while (window.isOpen()) {
    float deltaTime = appTimer.restart().asSeconds();

	while (window.pollEvent(evt)) {
		switch (evt.type)
		{
			// Track mouse movements.
		case sf::Event::MouseMoved:
			mouseXMoved = evt.mouseMove.x != mouseX;
			mouseYMoved = evt.mouseMove.y != mouseY;

			mouseX = evt.mouseMove.x;
			mouseY = evt.mouseMove.y;
			break;

		case sf::Event::KeyReleased:
			if (evt.key.code == sf::Keyboard::Key::Num1)
			{
				selected = left;

				windmill2.GetNode().RemoveChild(&windmill3.GetNode());
				windmill1.GetNode().RemoveChild(&windmill2.GetNode());

			}
			else if (evt.key.code == sf::Keyboard::Key::Num2)
			{
				selected = middle;

				windmill2.GetNode().RemoveChild(&windmill3.GetNode());
				windmill1.GetNode().RemoveChild(&windmill2.GetNode());

			}
			else if (evt.key.code == sf::Keyboard::Key::Num3)
			{
				selected = right;
				windmill2.GetNode().RemoveChild(&windmill3.GetNode());
				windmill1.GetNode().RemoveChild(&windmill2.GetNode());


			}
			else if (evt.key.code == sf::Keyboard::Key::Num4 || 
				evt.key.code == sf::Keyboard::Key::A)
			{
				selected = all;
				windmill1.setPosition(windmill1InitialPosition);
				windmill2.setPosition(windmill2RelativePosition);
				windmill3.setPosition(windmill3RelativePosition);

				windmill1.SetOrigin(windmill1Origin);
				windmill2.SetOrigin(windmill2Origin);
				windmill3.SetOrigin(windmill3Origin);

				windmill1.SetRotation(0.0f);
				windmill2.SetRotation(0.0f);
				windmill3.SetRotation(0.0f);

				windmill2.GetNode().AddChild(&windmill3.GetNode());
				windmill1.GetNode().AddChild(&windmill2.GetNode());

			}
			break;

		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
    }

    // do stuff.
    window.clear();
	//Rotate the vanes
	windmill1.RotateVanes(deltaTime*vaneSpeed);
	windmill2.RotateVanes(deltaTime*vaneSpeed);
	windmill3.RotateVanes(deltaTime*vaneSpeed);

	if (mouseYMoved)
	{
		switch (selected)
		{
		case left:
			windmill1.SetOrigin(windmill1Origin);
			windmill1.Rotate(deltaTime*windmillSpeed);
			break;

		case middle:
			windmill2.SetOrigin(windmill2SoloOrigin);
			windmill2.Rotate(deltaTime*windmillSpeed);
			break;

		case right:
			windmill3.SetOrigin(windmill3SoloOrigin);
			windmill3.Rotate(deltaTime*windmillSpeed);
			break;

		case all:
			windmill1.SetOrigin(windmill1Origin);
			windmill2.SetOrigin(windmill2Origin);
			windmill3.SetOrigin(windmill3Origin);
			windmill1.Rotate(deltaTime*windmillSpeed);
			windmill2.Rotate(deltaTime*windmillSpeed);
			windmill3.Rotate(deltaTime*windmillSpeed);
			break;
		}

		mouseYMoved = false;
	}

	windmill1.CenterOrigin();
	windmill2.CenterOrigin();
	windmill3.CenterOrigin();

	if (mouseXMoved)
	{

		switch (selected)
		{
		case left:
			//windmill1.CenterOrigin();
			windmill1.Rotate(deltaTime*windmillSpeed);
			break;

		case middle:
			//windmill2.CenterOrigin();
			windmill2.Rotate(deltaTime*windmillSpeed);
			break;

		case right:
			//windmill3.CenterOrigin();
			windmill3.Rotate(deltaTime*windmillSpeed);
			break;

		case all:
			//windmill1.CenterOrigin();
			//windmill2.CenterOrigin();
			//windmill3.CenterOrigin();
			windmill1.Rotate(deltaTime*windmillSpeed);
			windmill2.Rotate(deltaTime*windmillSpeed);
			windmill3.Rotate(deltaTime*windmillSpeed);
			break;
		}

		mouseXMoved = false;
	}

	background.setPosition(background.getPosition().x - deltaTime*bgSpeed, 0.0f);
	if(background.getPosition().x < -1024*3)
	{
		background.setPosition(0.0f, 0.0f);
	}


    //draw stuff
	//bodyNode1.Draw(&window);
	window.draw(background);

	switch (selected)
	{
	case left:
	case right:
	case middle:
		windmill1.GetNode().Draw(&window);
		windmill2.GetNode().Draw(&window);
		windmill3.GetNode().Draw(&window);
		break;

	case all:
		windmill1.GetNode().Draw(&window);
		break;
	}

    window.display();
  }

  return 0;
}