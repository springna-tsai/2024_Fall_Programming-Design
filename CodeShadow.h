#ifndef CODESHADOW_H
#define CODESHADOW_H

#include <string>
#include "Enemy.h"

class CodeShadow : public Enemy
{
private:
    std::string secretCode;
    int maxAttempts;
    int currentAttempts;

    struct GuessResult
    {
        int correctPosition; // A的數量
        int correctNumber;   // B的數量
    };

    // 生成隨機4位數密碼
    void generateSecretCode();

    // 延遲打印文字
    void printWithDelay(const std::string& text, int delay_ms = 25);

public:
    CodeShadow(const std::string& name = "符碼魔影");

    // 重寫攻擊方法
    void attack(Character& target) override;

    // 手動設置密碼
    void setSecretCode(const std::string& code);

    // 檢查玩家的猜測
    GuessResult checkGuess(const std::string& guess);

    // 檢查輸入是否合法
    bool isValidGuess(const std::string& guess);

    // 保存遊戲結果
    void saveGameResult(bool won, int attempts);
};

#endif
