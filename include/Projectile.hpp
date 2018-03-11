#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <Entity.hpp>
#include <ResourceIdentifier.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>


class Projectile : public Entity
{
    public:
        enum Type
        {
            ALLIES,
            ENEMY,
            MISSILE,
            SIZE
        };
    
    public:

        Projectile(Type type, const TextureHolder& textures);
    
        void guideTowards(sf::Vector2f position);
        bool isGuided() const;

        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

        float getMaxSpeed() const;
        int getDamage() const;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Type mType;
        sf::Sprite mSprite;
        sf::Vector2f mTargetDirection;
};

#endif // PROJECTILE_HPP