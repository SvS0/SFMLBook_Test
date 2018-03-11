#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include <SceneNode.hpp>

class Entity : public SceneNode
{
    public:

        explicit Entity(int hitPoints);

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);

        sf::Vector2f getVelocity() const;

        void accelerate(sf::Vector2f velocity);
        void accelerate(float vx, float vy);

        int getHitpoints() const;

        void heal(int points);
        void damage(int points);
        void destroy();

        bool isDestroyed() const;

    protected:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:

        sf::Vector2f mVelocity;
        int mHitpoints;
};

#endif // ENTITY_HPP
