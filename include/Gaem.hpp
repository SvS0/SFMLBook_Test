#ifndef GAEM_HPP
#define GAEM_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <StateStack.hpp>

class Gaem
{
    public:
        Gaem();
        void run();

    private:
        void processInput();
        void update(sf::Time dt);
        void render();

        void registerStates();

    private:
        static const sf::Time TimePerFrame;

        sf::RenderWindow mWindow;
        TextureHolder mTextures;
        FontHolder mFonts;
        Player mPlayer;

        StateStack mStateStack;

};

#endif // GAEM_HPP
