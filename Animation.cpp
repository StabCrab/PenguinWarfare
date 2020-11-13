//
// Created by trykr on 11.10.2020.
//

#include "Animation.h"

Animation::Animation(sf::Vector2u textureSize, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0.0;
    currentImage.x = 0;

    uvRect.width = textureSize.x / float(imageCount.x);
    uvRect.height = textureSize.y / float(imageCount.y);
}

void Animation::Update(unsigned int row, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    if (faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    uvRect.top = currentImage.y * uvRect.height;
}

Animation::~Animation()
{

}

sf::IntRect Animation::getUVRect() {
    return uvRect;
}
