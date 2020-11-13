//
// Created by trykr on 11.10.2020.
//

#ifndef WORMSPROTOTYPE_ANIMATION_H
#define WORMSPROTOTYPE_ANIMATION_H
#include "SFML/Graphics.hpp"
class Animation
{
public:

    void Update(unsigned int row, float deltaTime, bool faceRight);

    Animation(sf::Vector2u textureSize, sf::Vector2u imageCount, float switchTime);
    ~Animation();

    sf::IntRect getUVRect();
private:
    sf::IntRect uvRect;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
};


#endif //WORMSPROTOTYPE_ANIMATION_H
