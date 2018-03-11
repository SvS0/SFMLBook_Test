#include <Gaem.hpp>

#include <Utility.hpp>
#include <State.hpp>
#include <StateIdentifier.hpp>
#include <TitleState.hpp>
#include <GaemState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <SettingsState.hpp>

Gaem::Gaem()
: mWindow(sf::VideoMode(800, 600), "Test IT", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
    //enables/disable key press repeat
    mWindow.setKeyRepeatEnabled(false);

    mFonts.load(Fonts::MAIN, "resources/8bitOperatorPlus8-Bold.ttf");
    mTextures.load(Textures::LOGO, "resources/cb.bmp");
    mTextures.load(Textures::BUTTON_RED, "resources/redSheet.png");

    registerStates();
    mStateStack.pushState(States::TITLE);
}

const sf::Time Gaem::TimePerFrame = sf::seconds(1.f/60.f);

void Gaem::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if(mStateStack.isEmpty())
                mWindow.close();
        }

        render();
    }
}

void Gaem::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Gaem::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Gaem::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Gaem::registerStates()
{
    mStateStack.registerState<TitleState>(States::TITLE);
    mStateStack.registerState<MenuState>(States::MENU);
    mStateStack.registerState<GaemState>(States::GAEM);
    mStateStack.registerState<PauseState>(States::PAUSE);
    mStateStack.registerState<SettingsState>(States::SETTINGS);

    //mStateStack.registerState<LoadingState>(States::LOADING);
}
