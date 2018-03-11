#include <World.hpp>
#include <TextNode.hpp>

#include<SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds (0.f, 0.f,
    mWorldView.getSize().x,
    mWorldView.getSize().y)
, mSpawnPositionP1(
    mWorldView.getSize().x * 0.2f,
    mWorldView.getSize().y * 0.5f)
, mScrollSpeed(0.f)
, mP1(nullptr)
, mEnemySpawnPoints()
, mActiveEnemies()
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mWorldView.getSize().x * 0.5f,
                        mWorldView.getSize().y * 0.5f);
}

void World::loadTextures()
{
    mTextures.load(Textures::MAP, "resources/spritesheet_tiles.png");
    mTextures.load(Textures::LOGO, "resources/cb.bmp");
}

void World::buildScene()
{
    for(std::size_t i = 0; i < SIZE; ++i)
    {
        Category::Type category = (i == AIR) ? Category::SCENE : Category::NONE;
        
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    std::unique_ptr<Bar> p1 (new Bar(Bar::P1, mTextures, mFonts));
    mP1 = p1.get();
    mP1->setPosition(mSpawnPositionP1);
    mSceneLayers[AIR]->attachChild(std::move(p1));

    addEnemies();
}

void World::addEnemy(Bar::Type type, float relX, float relY)
{
    SpawnPoint spawn(type, 400 + relX, 500 - relY);
    mEnemySpawnPoints.push_back(spawn);
}

void World::addEnemies()
{
    addEnemy(Bar::P2, 0.f, 500.f);
    addEnemy(Bar::P2, -100.f, 400.f);
    addEnemy(Bar::P2, 140.f, 200.f);
    addEnemy(Bar::P2, 300.f, 400.f);
    addEnemy(Bar::P2, -200.f, 300.f);
    addEnemy(Bar::P2, 0.f, 600.f);
    
    std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
    {
        return lhs.y < rhs.y;
    });
}

void World::spawnEnemies()
{
    while (!mEnemySpawnPoints.empty()
            && mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();

        std::unique_ptr<Bar> enemy(new Bar(spawn.type, mTextures, mFonts));
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);

        mSceneLayers[AIR]->attachChild(std::move(enemy));

        mEnemySpawnPoints.pop_back();
    }
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() -mWorldView.getSize() / 2.f,
                        mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
    sf::FloatRect bounds = getViewBounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;

    return bounds;
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, 0.f);
    mP1->setVelocity(0.f, 0.f);

    destroyEntitiesOutsideView();
    guideMissiles();

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    
    adaptPlayerVelocity();

    handleCollisions();

    mSceneGraph.removeWrecks();
    spawnEnemies();

    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

bool World::hasAlivePlayer() const
{
    return !mP1->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
    return !mWorldBounds.contains(mP1->getPosition());
}

void World::adaptPlayerPosition()
{
    sf::FloatRect viewBounds = getViewBounds();
    const float borderDistance = 40.f;

    sf::Vector2f position = mP1->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mP1 -> setPosition(position);
}

void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mP1->getVelocity();
    
    if(velocity.x != 0.f && velocity.y != 0.f)
        mP1->setVelocity(velocity / std::sqrt(2.f));

    mP1->accelerate(0.f, mScrollSpeed);
}


bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    FOREACH(SceneNode::Pair pair, collisionPairs)
    {
        if(matchesCategories(pair, Category::P1, Category::ENEMY))
        {
            auto& player = static_cast<Bar&>(*pair.first);
            auto& enemy = static_cast<Bar&>(*pair.second);

            player.damage(enemy.getHitpoints());
            enemy.destroy();
        }
        else if(matchesCategories(pair, Category::ENEMY, Category::ALLIEDPROJECTILE)
                || matchesCategories(pair, Category::P1, Category::ENEMYPROJECTILE))
        {
            auto& aircraft = static_cast<Bar&>(*pair.first);
            auto& projectile = static_cast<Projectile&>(*pair.second);

            aircraft.damage(projectile.getDamage());
            projectile.destroy();
        }
    }
}

void World::destroyEntitiesOutsideView()
{
    Command command;
    command.category = Category::PROJECTILE | Category::ENEMY;
    command.action = derivedAction<Entity>([this] (Entity& e, sf::Time)
    {
        if(!getBattlefieldBounds().intersects(e.getBoundingRect()))
            e.destroy();
    });

    mCommandQueue.push(command);
}

void World::guideMissiles()
{
    Command enemyCollector;
    enemyCollector.category = Category::ENEMY;
    enemyCollector.action = derivedAction<Bar>([this] (Bar& enemy, sf::Time)
    {
        if(!enemy.isDestroyed())
            mActiveEnemies.push_back(&enemy);
    });

    Command missileGuider;
    missileGuider.category = Category::ALLIEDPROJECTILE;
    missileGuider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time)
    {
        if(!missile.isGuided())
            return;

        float minDistance = std::numeric_limits<float>::max();
        Bar* closestEnemy = nullptr;

        FOREACH(Bar* enemy, mActiveEnemies)
        {
            float enemyDistance = distance(missile, *enemy);

            if(enemyDistance < minDistance)
            {
                closestEnemy = enemy;
                minDistance = enemyDistance;
            }
        }

        if(closestEnemy)
            missile.guideTowards(closestEnemy->getWorldPosition());
    });

    mCommandQueue.push(enemyCollector);
    mCommandQueue.push(missileGuider);
    mActiveEnemies.clear();
}