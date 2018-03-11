#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <ResourceIdentifier.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>
#include <functional>


struct Direction
{
    Direction(float angle, float distance)
    : angle(angle)
    , distance(distance)
    { }

    float angle;
    float distance;
};

struct BodyData
{
    int hitpoints;
    float speed;
    sf::Time fireInterval;
    Textures::ID texture;
    std::vector<Direction> directions;
};

struct ProjectileData
{
    int damage;
    float speed;
    Textures::ID texture;
};

std::vector<BodyData> initializeBodyData();
std::vector<ProjectileData> initializeProjectileData();

#endif // DATATABLES_HPP
