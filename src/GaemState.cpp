#include <GaemState.hpp>

GaemState::GaemState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
, mPlayer(*context.player)
{ }

void GaemState::draw()
{
    mWorld.draw();
}

bool GaemState::update(sf::Time dt)
{
    mWorld.update(dt);

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeinput(commands);

    return true;
}

bool GaemState::handleEvent(const sf::Event& event)
{
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    if(event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::PAUSE);

    return true;
}
