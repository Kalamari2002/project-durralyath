#pragma once
#include "interface/Clickable.h"
class Token :
    public Clickable
{
private:
    sf::CircleShape portrait;
protected:
    void onHoverEnter() override;
    void onHoverExit() override;
public:
    Token(float xPos, float yPos, float radius);
    void setTexture(sf::Texture* texture);
    void setPosition(float xPos, float yPos) override;
    void draw(sf::RenderWindow& window) override;
};

