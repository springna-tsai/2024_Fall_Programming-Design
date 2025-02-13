#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(const std::string &n, int hp)
        : Character(n, hp) {}

    virtual void attack(Character &target) override
    {
        // 基礎攻擊邏輯
    }
};

#endif