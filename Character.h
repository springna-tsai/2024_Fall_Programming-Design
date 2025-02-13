#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character
{
protected:
    std::string name;
    int health;

public:
    Character(const std::string& n, int hp)
        : name(n), health(hp) {
    }

    std::string getName() const
    {
        return name;
    }

    int getHealth() const
    {
        return health;
    }

    // 新增 takeDamage 方法，用於減少角色血量
    void takeDamage(int dmg)
    {
        health -= dmg;
        if (health < 0)
            health = 0; // 確保血量不會為負
    }

    // 純虛函數，需由子類別實作
    virtual void attack(Character& target) = 0;

    virtual ~Character() = default; // 虛擬析構函數，確保正確釋放資源

    friend class CodeShadow; // 允許 CodeShadow 訪問 health
};

#endif
