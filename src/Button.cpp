#include <Button.hpp>

#include <Utility.hpp>

namespace GUI
{

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
: mCallback()
, mNormalRect(0, 0, 184, 40)
, mSelectedRect(0, 40, 184, 40)
, mPressedRect(0, 80, 184, 40)
, mButtonTexture(textures.get(Textures::BUTTON_RED))
, mSprite()
, mText("", fonts.get(Fonts::MAIN), 16)
{
    mSprite.setTexture(mButtonTexture);
    mSprite.setTextureRect(mNormalRect);

    sf::FloatRect bounds = mSprite.getLocalBounds();
    mText.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);
}

void Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}

void Button::setToggle(bool flag)
{
    mIsToggle = flag;
}

bool Button::isSelectable() const
{
    return true;
}

void Button::select()
{
    Component::select();
    mSprite.setTextureRect(mSelectedRect);
}

void Button::deselect()
{
    Component::deselect();
    mSprite.setTextureRect(mNormalRect);
}

void Button::activate()
{
    Component::activate();
    if (mIsToggle)
        mSprite.setTextureRect(mPressedRect);
    if (mCallback)
        mCallback();
    if (!mIsToggle)
        deactivate();
}

void Button::deactivate()
{
    Component::deactivate();
    if (mIsToggle)
    {
        if (isSelected())
            mSprite.setTextureRect(mSelectedRect);
        else
            mSprite.setTextureRect(mNormalRect);
    }
}

void Button::handleEvent(const sf::Event&) { }

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

}
