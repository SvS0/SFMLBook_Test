#ifndef RESOURCEIDENTIFIER_HPP
#define RESOURCEIDENTIFIER_HPP

#include <ResourceHolder.hpp>

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        MAP,
        LOGO,
        BUTTON_RED,
        SIZE,
    };
}

namespace Fonts
{
    enum ID
    {
        MAIN,
        SIZE
    };
}

namespace Sounds
{
    enum ID
    {
        SIZE
    };
}

namespace Musics
{
    enum ID
    {
        SIZE
    };
}

namespace Shaders
{
    enum ID
    {
        SIZE
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIER_HPP
