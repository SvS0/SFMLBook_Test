#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
    enum Type
    {
        NONE = 0,
        SCENE = 1 << 0,
        P1 = 1 << 1,
        P2 = 1 << 2,
        ALLIEDPROJECTILE = 1 << 3,
        ENEMYPROJECTILE = 1 << 4,

        BAR = P1 | P2,
        ENEMY = P2,
        PROJECTILE = ALLIEDPROJECTILE | ENEMYPROJECTILE,
    };
}

#endif // CATEGORY_HPP
