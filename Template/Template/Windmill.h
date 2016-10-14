#ifndef _WINDMILL_H_
#define _WINDMILL_H_
#include "TransformNode.h"

//Initial Values

class Windmill
{
public:
	Windmill();
	Windmill(sf::Vector2f position);

	void setPosition(sf::Vector2f position);

	void Draw(sf::RenderTarget *target);

	TransformNode& GetNode();

	void RotateVanes(float degrees);

	void Rotate(float degrees);

	void SetRotation(float degrees);

	void CenterOrigin();

	void SetOrigin(sf::Vector2f origin);

protected:
	sf::ConvexShape body;
	TransformNode bodyNode;
	sf::Vector2<float> baseSize;
	sf::RectangleShape base;
	sf::RectangleShape pinWheel;
	sf::RectangleShape blade1;
	sf::RectangleShape blade2;
	sf::RectangleShape blade3;
	sf::RectangleShape blade4;
	TransformNode baseNode;
	TransformNode pinWheelNode;
	TransformNode blade1Node;
	TransformNode blade2Node;
	TransformNode blade3Node;
	TransformNode blade4Node;
	sf::Texture bladeTextureHorizontal;
	sf::Texture bladeTextureVertical;
	sf::Texture bodyTexture;
};

#endif