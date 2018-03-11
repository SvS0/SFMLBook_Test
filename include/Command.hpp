#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>

#include <Category.hpp>

#include <cassert>
#include <functional>


class SceneNode;

struct Command
{
    Command();

    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;
};

template <typename GaemObject, typename Function>
std::function <void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [=] (SceneNode& node, sf::Time dt)
    {
        assert(dynamic_cast<GaemObject*>(&node) != nullptr);

        fn(static_cast<GaemObject&>(node), dt);
    };
}

#endif // COMMAND_HPP
