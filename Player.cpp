#include "Player.h"
#include <iostream>

Player::Player(const std::string& n)
    : Character(n, 100), level(0), experience(0) {
}

int Player::getExperience() const {
    return experience; // 返回經驗值，目前不使用
}

void Player::attack(Character& target) {
    // 玩家無法攻擊，僅打印提示訊息
    std::cout << name << " 無法攻擊其他目標！\n";
}

bool Player::isDefeated() const {
    return health <= 0; // 當玩家血量 <= 0，表示被打敗
}
