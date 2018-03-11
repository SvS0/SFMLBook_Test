#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include <SFML/Graphics.hpp>

#include <Utility.hpp>

#include <State.hpp>
#include <ResourceHolder.hpp>

#include <ParallelTask.hpp>


class LoadingState : public State
{
    public:
        LoadingState(StateStack& stack, Context context);

        virtual void draw();
        virtual bool update(sf::Time);
        virtual bool handleEvent(const sf::Event& event);

    private:

        void setCompletion(float percent);

    private:

        sf::Text mLoadingText;
        sf::RectangleShape mProgressBarBackground;
        sf::RectangleShape mProgressBar;

        ParallelTask mLoadingTask;
};

#endif // LOADINGSTATE_HPP
