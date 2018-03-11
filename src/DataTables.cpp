#include <DataTables.hpp>
#include <Bar.hpp>
#include <Projectile.hpp>

std::vector<BodyData> initializeBodyData()
{
    std::vector<BodyData> data(Bar::SIZE);

    data[Bar::P1].hitpoints = 100;
    data[Bar::P1].speed = 200.f;
    data[Bar::P1].fireInterval = sf::seconds(1.f);
    data[Bar::P1].texture = Textures::LOGO;

    data[Bar::P2].hitpoints = 20;
    data[Bar::P2].speed = 80.f;
    data[Bar::P2].fireInterval = sf::seconds(1.2f);
    data[Bar::P2].texture = Textures::LOGO;
    data[Bar::P2].directions.push_back(Direction(45,  50));
    data[Bar::P2].directions.push_back(Direction(0, 50));
    data[Bar::P2].directions.push_back(Direction(-45,  100));
    data[Bar::P2].directions.push_back(Direction(0,  50));
    data[Bar::P2].directions.push_back(Direction(45, 50));

    return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::SIZE);

    data[Projectile::ALLIES].damage = 1;
    data[Projectile::ALLIES].speed = 10.f;
    data[Projectile::ALLIES].texture = Textures::LOGO;

    data[Projectile::MISSILE].damage = 2;
    data[Projectile::MISSILE].speed = 100.f;
    data[Projectile::MISSILE].texture = Textures::LOGO;

    data[Projectile::ENEMY].damage = 1;
    data[Projectile::ENEMY].speed = 50.f;
    data[Projectile::ENEMY].texture = Textures::LOGO;


    
    return data;
}
