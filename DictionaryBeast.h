#ifndef DICTIONARYBEAST_H
#define DICTIONARYBEAST_H

#include "Enemy.h"
#include <string>
#include <vector>

class DictionaryBeast : public Enemy {
private:
    std::vector<std::string> wordPool6; // 6 字母單字池
    std::vector<std::string> wordPool7; // 7 字母單字池
    std::vector<std::string> wordPool8; // 8 字母單字池
    int maxRounds;                      // 最大回合數
    int currentRound;                   // 當前回合數

    // 工具方法
    std::string shuffleWord(const std::string& word) const;
    std::string toLowerCase(const std::string& word) const;
    std::string getScrambledWord(const std::string& word) const;
    std::string getWordForRound();

    // 延遲打印文字
    void printWithDelay(const std::string& text, int delay_ms = 25);

public:
    DictionaryBeast(const std::string& name, const std::string& wordFile);

    // 重寫攻擊方法
    void attack(Character& target) override;
};

#endif
