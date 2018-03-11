#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <State.hpp>
#include <Container.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>



class MenuState : public State
{

    public:
        MenuState(StateStack& stack, Context context);

        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);

    private:
        GUI::Container mGUIContainer;

        sf::Sprite mBackgroundSprite;
};

#endif // MENUSTATE_HPP
