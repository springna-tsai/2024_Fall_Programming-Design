#ifndef GUARDIAN_H
#define GUARDIAN_H

#include "Enemy.h"
#include <vector>
#include <string>
#include <utility>

class Guardian : public Enemy {
private:
    std::vector<std::string> MBTI_TYPES;
    std::vector<std::pair<std::string, std::vector<std::string>>> QUESTIONS;
    std::string targetMBTI;

    std::string generateTargetMBTI();
    std::string calculateMBTI(const std::vector<int>& answers);
    void printWithDelay(const std::string& text, int delay_ms = 25);

public:
    Guardian(const std::string& n); // 修改構造函式

    void attack(Character& target) override;
};

#endif
