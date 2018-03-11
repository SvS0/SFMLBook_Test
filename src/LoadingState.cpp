#include <LoadingState.hpp>

LoadingState::LoadingState(StateStack& stack, Context context)
: State(stack, context)
{
    sf::RenderWindow& window = *getContext().window;
    sf::Font& font = context.fonts->get(Fonts::MAIN);
    sf::Vector2f viewSize = window.getView().getSize();

    mLoadingText.setFont(font);
    mLoadingText.setString("Loading, please wait");
    centerOrigin(mLoadingText);
    mLoadingText.setPosition(viewSize.x * 0.5f,
                             viewSize.y * 0.5f + 50);

    mProgressBarBackground.setFillColor(sf::Color::White);
    mProgressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10.f));
    mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);

    mProgressBar.setFillColor(sf::Color(100,100,100));
    mProgressBar.setSize(sf::Vector2f(200, 10));
    mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);

    setCompletion(0.f);

    mLoadingTask.execute();
}

void LoadingState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mLoadingText);
    window.draw(mProgressBarBackground);
    window.draw(mProgressBar);
}

bool LoadingState::update(sf::Time dt)
{
    if(mLoadingTask.isFinished())
    {
        requestStackPop();
        requestStackPush(States::GAEM);
    }
    else
    {
        setCompletion(mLoadingTask.getCompletion());
    }

    return true;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
    return true;
}

void LoadingState::setCompletion(float percent)
{
    if (percent > 1.f)
        percent = 1.f;

    mProgressBar.setSize(sf::Vector2f(
            mProgressBarBackground.getSize().x * percent,
            mProgressBar.getSize().y));
}
