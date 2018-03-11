#include <Player.hpp>
#include <Bar.hpp>
#include <Foreach.hpp>

#include <string>
#include <algorithm>


struct BarMover
{
    BarMover(float vx, float vy)
    : velocity(vx, vy) { }

    void operator() (Bar& bar, sf::Time) const
    {
        bar.accelerate(velocity * bar.getMaxSpeed());
    }

    sf::Vector2f velocity;
};

Player::Player() :
    mCurrentMissionStatus(MissionRunning)
{
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Space] = Fire;
    mKeyBinding[sf::Keyboard::M] = LaunchMissile;


    initializeActions();

    FOREACH(auto& pair, mActionBinding)
        pair.second.category = Category::P1;
}

void Player::handleEvent(const sf::Event& event,
                        CommandQueue& commands)
{
    if(event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);
        if(found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
    
}

void Player::handleRealtimeinput(CommandQueue& commands)
{
    FOREACH(auto pair, mKeyBinding)
    {
        if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(mActionBinding[pair.second]);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
    {
        if(itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }
        mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    FOREACH(auto pair, mKeyBinding)
    {
        if(pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
    const float playerSpeed = 2.f;

    mActionBinding[MoveUp].action = derivedAction<Bar>(BarMover(0, -1));
    mActionBinding[MoveDown].action = derivedAction<Bar>(BarMover(0, 1));
    mActionBinding[MoveLeft].action = derivedAction<Bar>(BarMover(-1, 0));
    mActionBinding[MoveRight].action = derivedAction<Bar>(BarMover(1, 0));
    mActionBinding[Fire].action = derivedAction<Bar>([] (Bar& a, sf::Time) { a.fire(); });
    mActionBinding[LaunchMissile].action = derivedAction<Bar>([] (Bar& a, sf::Time) { a.launchMissile(); });
}

Player::MissionStatus Player::getMissionStatus() const
{
    return mCurrentMissionStatus;
}

void Player::setMissionStatus(MissionStatus status) 
{
    mCurrentMissionStatus = status;
}

bool Player::isRealtimeAction(Action action)
{
    switch(action)
    {
        case MoveUp:
        case MoveDown:
        case MoveLeft:
        case MoveRight:
        case Fire:
            return true;
            break;
        default:
            return false;
            break;
    }
}
