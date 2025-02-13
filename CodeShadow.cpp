#include "CodeShadow.h"
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>

CodeShadow::CodeShadow(const std::string& name)
    : Enemy(name, 100), maxAttempts(10), currentAttempts(0)
{
    generateSecretCode();
}

void CodeShadow::generateSecretCode()
{
    if (!secretCode.empty())
        return; // 如果密碼已設置，則跳過生成

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    secretCode = "";
    while (secretCode.length() < 4)
    {
        char digit = '0' + dis(gen);
        if (secretCode.find(digit) == std::string::npos)
        {
            secretCode += digit;
        }
    }
}

bool CodeShadow::isValidGuess(const std::string& guess)
{
    if (guess.length() != 4)
        return false;

    for (char c : guess)
    {
        if (!isdigit(c))
            return false;
    }

    for (size_t i = 0; i < guess.length(); i++)
    {
        for (size_t j = i + 1; j < guess.length(); j++)
        {
            if (guess[i] == guess[j])
                return false;
        }
    }

    return true;
}

CodeShadow::GuessResult CodeShadow::checkGuess(const std::string& guess)
{
    GuessResult result = { 0, 0 };

    for (size_t i = 0; i < 4; i++)
    {
        if (guess[i] == secretCode[i])
        {
            result.correctPosition++;
        }
        else if (secretCode.find(guess[i]) != std::string::npos)
        {
            result.correctNumber++;
        }
    }

    return result;
}

void CodeShadow::printWithDelay(const std::string& text, int delay_ms) {
    for (size_t i = 0; i < text.size(); ++i) {
        std::cout << text[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

void CodeShadow::attack(Character& target)
{
    printWithDelay("\n符碼魔影出現了！\n", 50);
    printWithDelay("你必須在" + std::to_string(maxAttempts) + "次內猜出4位數密碼。\n", 50);
    printWithDelay("每個數字都不同，我會告訴你有多少A和多少B。\n", 50);

    while (currentAttempts < maxAttempts)
    {
        std::string guess;
        printWithDelay("請輸入你的猜測 (還剩" + std::to_string(maxAttempts - currentAttempts) + "次): \n", 50);
        std::cin >> guess;

        try
        {
            if (!isValidGuess(guess))
            {
                throw std::invalid_argument("無效的輸入！請輸入4個不重複的數字。\n");
            }

            currentAttempts++;
            GuessResult result = checkGuess(guess);

            printWithDelay(std::to_string(result.correctPosition) + "A" + std::to_string(result.correctNumber) + "B\n", 50);

            if (result.correctPosition == 4)
            {
                printWithDelay("恭喜你猜對了！\n", 50);
                saveGameResult(true, currentAttempts);
                return;
            }
        }
        catch (const std::invalid_argument& e)
        {
            printWithDelay(e.what(), 50);
            continue;
        }
    }

    printWithDelay("遊戲結束！正確答案是: " + secretCode, 50);
    saveGameResult(false, currentAttempts);
    target.takeDamage(100); // 失敗時對玩家造成傷害
}

void CodeShadow::saveGameResult(bool won, int attempts)
{
    std::ofstream file("sources/game_results.txt", std::ios::app);
    if (file.is_open())
    {
        file << "遊戲結果: " << (won ? "勝利" : "失敗")
            << ", 嘗試次數: " << attempts
            << ", 密碼: " << secretCode << "\n";
        file.close();
    }
}

void CodeShadow::setSecretCode(const std::string& code)
{
    if (code.length() != 4 || !isValidGuess(code))
    {
        throw std::invalid_argument("無效的密碼！密碼必須是4個不重複的數字。\n");
    }
    secretCode = code;
}
