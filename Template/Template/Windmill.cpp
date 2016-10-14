#include "Windmill.h"

Windmill::Windmill()
{
	//Sizes
	//sf::Vector2f baseSizeSmall(55.0f, 10.0f);
	sf::Vector2f baseSizeLarge(110.0f, 20.0f);
	//sf::Vector2f baseSize(55.0f, 10.0f);
	//sf::Vector2f baseSize(55.0f, 10.0f);
	sf::Vector2f bladeSizeHorizontal(200.0f, 50.0f);
	sf::Vector2f bladeSizeVertical(50.0f, 200.0f);

	//Textures
	bladeTextureHorizontal.loadFromFile("res/Canvas_200x50.jpg");
	bladeTextureVertical.loadFromFile("res/Canvas_50x200.jpg");
	bodyTexture.loadFromFile("res/Body_Texture.jpg");

	body.setPointCount(4);
	body.setPoint(0, sf::Vector2f(40, 0));
	body.setPoint(1, sf::Vector2f(60, 0));
	body.setPoint(2, sf::Vector2f(100, 300));
	body.setPoint(3, sf::Vector2f(0, 300));
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
	body.setTexture(&bodyTexture);

	//Draw the windmill base shapes
	base.setSize(baseSizeLarge);
	base.setOrigin(base.getSize().x / 2, 0);
	base.setPosition(0, body.getLocalBounds().height/2);
	base.setFillColor(sf::Color::Cyan);

	//sf::ConvexShape pinWheel;
	pinWheel.setSize(sf::Vector2f(20.0f, 20.0f));
	/*pinWheel.setPointCount(12);
	pinWheel.setPoint(0, sf::Vector2f(8, 0));
	pinWheel.setPoint(1, sf::Vector2f(12, 0));
	pinWheel.setPoint(2, sf::Vector2f(12, 8));
	pinWheel.setPoint(3, sf::Vector2f(20, 8));
	pinWheel.setPoint(4, sf::Vector2f(20, 12));
	pinWheel.setPoint(5, sf::Vector2f(12, 12));
	pinWheel.setPoint(6, sf::Vector2f(12, 20));
	pinWheel.setPoint(7, sf::Vector2f(8, 20));
	pinWheel.setPoint(8, sf::Vector2f(8, 12));
	pinWheel.setPoint(9, sf::Vector2f(0, 12));
	pinWheel.setPoint(10, sf::Vector2f(0, 8));
	pinWheel.setPoint(11, sf::Vector2f(8, 8));
	pinWheel.setOrigin(pinWheel.getLocalBounds().width / 2, pinWheel.getLocalBounds().height / 2);*/
	pinWheel.setOrigin(pinWheel.getSize().x / 2, pinWheel.getSize().y / 2);
	pinWheel.setPosition(0, -body.getLocalBounds().height / 4);
	pinWheel.setFillColor(sf::Color::Green);

	blade1.setSize(bladeSizeHorizontal);
	blade1.setOrigin(-2, blade1.getSize().y + 2);
	blade1.setTexture(&bladeTextureHorizontal);

	blade2.setSize(bladeSizeVertical);
	blade2.setOrigin(-2, -2);
	//blade2.setPosition(2, 2);
	blade2.setTexture(&bladeTextureVertical);

	blade3.setSize(bladeSizeHorizontal);
	blade3.setOrigin(blade3.getSize().x + 2, -2);
	//blade3.setPosition(-2, 2);
	blade3.setTexture(&bladeTextureHorizontal);

	blade4.setSize(bladeSizeVertical);
	blade4.setOrigin(blade4.getSize().x + 2, blade4.getSize().y + 2);
	//blade4.setPosition(-2, -2);
	blade4.setTexture(&bladeTextureVertical);

	bodyNode = TransformNode(&body);
	baseNode = TransformNode(&base);
	pinWheelNode = TransformNode(&pinWheel);
	blade1Node = TransformNode(&blade1);
	blade2Node = TransformNode(&blade2);
	blade3Node = TransformNode(&blade3);
	blade4Node = TransformNode(&blade4);

	pinWheelNode.AddChild(&blade1Node);
	pinWheelNode.AddChild(&blade2Node);
	pinWheelNode.AddChild(&blade3Node);
	pinWheelNode.AddChild(&blade4Node);

	bodyNode.AddChild(&baseNode);
	bodyNode.AddChild(&pinWheelNode);
}

Windmill::Windmill(sf::Vector2f position)
{
	Windmill();
	this->setPosition(position);
}

void Windmill::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

void Windmill::Draw(sf::RenderTarget *target)
{
	bodyNode.Draw(target);
}

TransformNode& Windmill::GetNode()
{
	return bodyNode;
}

void Windmill::RotateVanes(float degrees)
{
	pinWheel.rotate(degrees);
	blade1.rotate(degrees);
	blade2.rotate(degrees);
	blade3.rotate(degrees);
	blade4.rotate(degrees);
}

void Windmill::Rotate(float degrees)
{
	body.rotate(degrees);
}

void Windmill::SetRotation(float degrees)
{
	body.setRotation(degrees);
}

void Windmill::CenterOrigin()
{
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
}

void Windmill::SetOrigin(sf::Vector2f origin)
{
	body.setOrigin(origin);
}
