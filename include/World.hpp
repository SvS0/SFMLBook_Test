#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <array>
#include <queue>

#include <SceneNode.hpp>
#include <Bar.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <CommandQueue.hpp>

namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
    public:
        explicit World(sf::RenderWindow& window, FontHolder& fonts);
        void update(sf::Time dt);
        void draw();

        CommandQueue& getCommandQueue();

        bool hasAlivePlayer() const;
        bool hasPlayerReachedEnd() const;

    private:
        void loadTextures();
        void adaptPlayerPosition();
        void adaptPlayerVelocity();
        void handleCollisions();

        void buildScene();
        void spawnEnemies();
        void addEnemy(Bar::Type type, float relX, float relY);
        void addEnemies();
        void destroyEntitiesOutsideView();
        void guideMissiles();

        sf::FloatRect getBattlefieldBounds() const;
        sf::FloatRect getViewBounds() const;

    private:
        enum Layer
        {
            BACKGROUND,
            AIR,
            SIZE
        };

        struct SpawnPoint
        {
            SpawnPoint(Bar::Type type, float x, float y)
            : type(type)
            , x(x)
            , y(y)
            { }

            Bar::Type type;
            float x;
            float y;
        };

    private:
        sf::RenderWindow& mWindow;
        sf::View mWorldView;
        TextureHolder mTextures;
        FontHolder& mFonts;

        CommandQueue mCommandQueue;

        SceneNode mSceneGraph;
        std::array<SceneNode*, SIZE> mSceneLayers;

        sf::FloatRect mWorldBounds;
        sf::Vector2f mSpawnPositionP1;
        sf::Vector2f mSpawnPositionP2;
        float mScrollSpeed;
        Bar* mP1;

        std::vector<SpawnPoint> mEnemySpawnPoints;
        std::vector<Bar*> mActiveEnemies;
};

#endif // WORLD_HPP
