#ifndef GAEMSTATE_HPP
#define GAEMSTATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <World.hpp>
#include <Player.hpp>

class GaemState : public State
{
    public:
        GaemState(StateStack& stack, Context context);

        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);

    private:
        World mWorld;
        Player& mPlayer;
};

#endif // GAEMSTATE_HPP
