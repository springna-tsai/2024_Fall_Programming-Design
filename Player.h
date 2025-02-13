#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    int level;       // 等級（目前不使用，但保留）
    int experience;  // 經驗（目前不使用，但保留）

public:
    Player(const std::string& n);

    // 獲取經驗值，暫時無實際用途
    int getExperience() const;

    // 玩家無法攻擊，留空實現
    void attack(Character& target) override;

    // 檢查玩家是否被打敗
    bool isDefeated() const;
};

#endif
