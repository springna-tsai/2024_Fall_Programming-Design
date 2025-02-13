#include "DictionaryBeast.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <random>
#include <chrono>
#include <thread>

DictionaryBeast::DictionaryBeast(const std::string& name, const std::string& wordFile)
    : Enemy(name, 100), maxRounds(3), currentRound(1) {
    std::ifstream file(wordFile);
    if (!file) {
        throw std::runtime_error("無法打開單字檔案！");
    }

    std::string word;
    while (file >> word) {
        if (word.length() == 6) {
            wordPool6.push_back(word);
        }
        else if (word.length() == 7) {
            wordPool7.push_back(word);
        }
        else if (word.length() == 8) {
            wordPool8.push_back(word);
        }
    }

    if (wordPool6.empty() || wordPool7.size() < 3 || wordPool8.size() < 2) {
        throw std::runtime_error("單字庫中符合長度條件的單字數量不足！");
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wordPool6.begin(), wordPool6.end(), g);
    std::shuffle(wordPool7.begin(), wordPool7.end(), g);
    std::shuffle(wordPool8.begin(), wordPool8.end(), g);
}

std::string DictionaryBeast::shuffleWord(const std::string& word) const {
    std::string shuffled = word;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), g);
    return shuffled;
}

std::string DictionaryBeast::toLowerCase(const std::string& word) const {
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    return lowercaseWord;
}

std::string DictionaryBeast::getScrambledWord(const std::string& word) const {
    std::string remaining = word.substr(1);
    std::string scrambled = remaining;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(scrambled.begin(), scrambled.end(), g);
    return scrambled;
}

std::string DictionaryBeast::getWordForRound() {
    if (currentRound == 1) {
        return wordPool6.back();
    }
    else if (currentRound >= 2 && currentRound <= 4) {
        return wordPool7.back();
    }
    else {
        return wordPool8.back();
    }
}
void DictionaryBeast::printWithDelay(const std::string& text, int delay_ms) {
    for (size_t i = 0; i < text.size(); ++i) {
        std::cout << text[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

void DictionaryBeast::attack(Character& target) {
    printWithDelay("辭典巨獸出現！你需要拼出正確的單字來阻止它的攻擊！\n");
    printWithDelay("遊戲規則：\n");
    printWithDelay("- 共有 3 回合，每回合有 3 次機會。\n");
    printWithDelay("- 每回合你需要根據提示拼出正確的單字。\n");

    for (currentRound = 1; currentRound <= maxRounds; ++currentRound) {
        std::string word = getWordForRound();
        if (currentRound == 1)
            wordPool6.pop_back();
        else if (currentRound >= 2 && currentRound <= 4)
            wordPool7.pop_back();
        else
            wordPool8.pop_back();

        std::string scrambled = getScrambledWord(word);

        printWithDelay("\n=== 回合 " + std::to_string(currentRound) + " ===\n");
        printWithDelay("單字首字母：'" + std::string(1, word[0]) + "'\n");
        printWithDelay("單字長度：" + std::to_string(word.length()) + " 字母\n");
        printWithDelay("打亂的字母：'" + scrambled + "'\n");

        bool guessedCorrectly = false;
        for (int attempts = 1; attempts <= 3; ++attempts) {
            printWithDelay("請輸入正確的單字（第 " + std::to_string(attempts) + " 次嘗試）：\n");
            std::string playerInput;
            std::cin >> playerInput;

            if (playerInput.length() != word.length()) {
                printWithDelay("輸入錯誤！單字應該包含 " + std::to_string(word.length()) + " 個字母！\n");
                continue;
            }

            if (toLowerCase(playerInput) == toLowerCase(word)) {
                printWithDelay("正確！你成功通過回合 " + std::to_string(currentRound) + "！\n");
                guessedCorrectly = true;
                break;
            }
            else {
                printWithDelay("錯誤！請再試一次。\n");
            }
        }

        if (!guessedCorrectly) {
            printWithDelay("你未能通過回合 " + std::to_string(currentRound) + "。\n");
            printWithDelay("正確答案是：'" + word + "'\n");
            printWithDelay("辭典巨獸對你造成 100 點傷害！\n");
            target.takeDamage(100);
            return;
        }
    }

    printWithDelay("恭喜！你成功擊敗了辭典巨獸！\n");
}
