#include "Player.h"
#include "Guardian.h"
#include "DictionaryBeast.h"
#include "CodeShadow.h"
#include <vector>
#include <memory>
#include <random>
#include <iostream>

int main() {
    try {
        Player player("Player");

        // 初始化敵人列表
        std::vector<std::unique_ptr<Enemy>> enemies;
        enemies.push_back(std::unique_ptr<Enemy>(new Guardian("Guardian")));
        enemies.push_back(std::unique_ptr<Enemy>(new DictionaryBeast("DictionaryBeast", "sources/wordlist.txt")));

        // 初始化 CodeShadow 並設置密碼
        std::unique_ptr<CodeShadow> codeShadow(new CodeShadow("CodeShadow"));
        codeShadow->setSecretCode("1234"); // 設置固定密碼
        enemies.push_back(std::move(codeShadow));

        // 隨機打亂敵人順序
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(enemies.begin(), enemies.end(), g);

        std::cout << "遊戲開始！\n";

        for (auto& enemy : enemies) {
            std::cout << "遇到敵人：" << enemy->getName() << "！\n";
            enemy->attack(player);

            if (player.isDefeated()) {
                std::cout << player.getName() << " 被擊敗！遊戲結束。\n";
                return 0;
            }
        }

        std::cout << "恭喜你，擊敗了所有敵人！\n";
    }
    catch (const std::exception& e) {
        std::cerr << "錯誤： " << e.what() << "\n";
        std::cerr << "請確認所需檔案（例如 wordlist.txt）是否存在，並重新執行程式。\n";
    }

    return 0;
}
