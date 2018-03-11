#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <cassert>
#include <memory>
#include <vector>
#include <set>

#include <Foreach.hpp>
#include <Category.hpp>
#include <Command.hpp>


struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable,
                    private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        typedef std::pair<SceneNode*, SceneNode*> Pair;

    public:
        explicit SceneNode(Category::Type category = Category::NONE);

        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);

        void update(sf::Time dt, CommandQueue& commands);

        sf::Transform getWorldTransform() const;
        sf::Vector2f getWorldPosition() const;

        void onCommand(const Command&, sf::Time dt);
        virtual unsigned int getCategory() const;

        void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
        void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
        void removeWrecks();    
        virtual sf::FloatRect getBoundingRect() const;
        virtual bool isMarkedForRemoval() const;
        virtual bool isDestroyed() const;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
        void updateChildren(sf::Time dt, CommandQueue& commands);
        
        virtual void draw(sf::RenderTarget& target,
            sf::RenderStates states) const;

        virtual void drawCurrent(sf::RenderTarget& target,
            sf::RenderStates states) const;

        void drawChildren(sf::RenderTarget& target,
            sf::RenderStates states) const;
        
        void drawBoundingRect(sf::RenderTarget& target,
             sf::RenderStates states) const;

    private:
        std::vector<Ptr> mChildren;
        SceneNode* mParent;
        Category::Type mDefaultCategory;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_HPP