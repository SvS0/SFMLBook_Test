#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>

#include <Command.hpp>
#include <CommandQueue.hpp>

#include <map>

class Player
{
    public:
        enum Action
        {
            MoveUp,
            MoveDown,
            MoveLeft,
            MoveRight,
            Fire,
            LaunchMissile,
            ActionCount
        };

        enum MissionStatus
        {
            MissionRunning,
            MissionSuccess,
            MissionFailure
        };

    public:

        Player();

        void handleEvent (const sf::Event& event,
                        CommandQueue& commands);
        void handleRealtimeinput(CommandQueue& commands);

        void assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key getAssignedKey(Action action) const;

        void setMissionStatus(MissionStatus status);
        MissionStatus getMissionStatus() const;
    private:
        void initializeActions();
        static bool isRealtimeAction(Action action);

    private:
        std::map<sf::Keyboard::Key, Action> mKeyBinding;
        std::map<Action, Command> mActionBinding;
        MissionStatus mCurrentMissionStatus;
};

#endif // PLAYER_HPP
