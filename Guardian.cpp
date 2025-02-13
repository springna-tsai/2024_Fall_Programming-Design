#include "Guardian.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

// 構造函式，固定血量為 100
Guardian::Guardian(const std::string& n) : Enemy(n, 100) {
    MBTI_TYPES.push_back("ISTJ");
    MBTI_TYPES.push_back("ISFJ");
    MBTI_TYPES.push_back("INFJ");
    MBTI_TYPES.push_back("INTJ");
    MBTI_TYPES.push_back("ISTP");
    MBTI_TYPES.push_back("ISFP");
    MBTI_TYPES.push_back("INFP");
    MBTI_TYPES.push_back("INTP");
    MBTI_TYPES.push_back("ESTP");
    MBTI_TYPES.push_back("ESFP");
    MBTI_TYPES.push_back("ENFP");
    MBTI_TYPES.push_back("ENTP");
    MBTI_TYPES.push_back("ESTJ");
    MBTI_TYPES.push_back("ESFJ");
    MBTI_TYPES.push_back("ENFJ");
    MBTI_TYPES.push_back("ENTJ");

    std::vector<std::string> answers1;
    answers1.push_back("1. 我更喜歡獨處並內省。");
    answers1.push_back("2. 我更喜歡參與社交活動並與人交流。");
    QUESTIONS.push_back(std::make_pair("在休閒時間，你通常會選擇：", answers1));

    std::vector<std::string> answers2;
    answers2.push_back("1. 我注重具體細節和實際應用。");
    answers2.push_back("2. 我喜歡探索抽象概念和未來可能性。");
    QUESTIONS.push_back(std::make_pair("當處理資訊時，你傾向於：", answers2));

    std::vector<std::string> answers3;
    answers3.push_back("1. 我依靠邏輯與客觀數據來做決定。");
    answers3.push_back("2. 我關注個人價值和他人感受來做決定。");
    QUESTIONS.push_back(std::make_pair("當面臨選擇時，你更傾向於：", answers3));

    std::vector<std::string> answers4;
    answers4.push_back("1. 我喜歡計劃一切並提前安排。");
    answers4.push_back("2. 我更喜歡靈活應對和順其自然。");
    QUESTIONS.push_back(std::make_pair("你的生活方式更符合：", answers4));

    srand(static_cast<unsigned>(time(nullptr)));
    targetMBTI = generateTargetMBTI();
}

std::string Guardian::generateTargetMBTI() {
    return MBTI_TYPES[rand() % MBTI_TYPES.size()];
}

std::string Guardian::calculateMBTI(const std::vector<int>& answers) {
    std::string result;
    result += (answers[0] == 1) ? 'I' : 'E';
    result += (answers[1] == 1) ? 'S' : 'N';
    result += (answers[2] == 1) ? 'T' : 'F';
    result += (answers[3] == 1) ? 'J' : 'P';
    return result;
}

void Guardian::printWithDelay(const std::string& text, int delay_ms) {
    for (size_t i = 0; i < text.size(); ++i) {
        std::cout << text[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << std::endl; // 保證每段文字結束後換行
}

void Guardian::attack(Character& target) {
    printWithDelay("人格守衛開始攻擊！\n");
    printWithDelay("您需要回答四個問題來完成 MBTI 測試。\n");
    printWithDelay("人格守衛正在尋找：" + targetMBTI + " 型的人！\n\n");

    std::vector<int> answers;
    for (size_t i = 0; i < QUESTIONS.size(); ++i) {
        printWithDelay(QUESTIONS[i].first + "\n");
        printWithDelay(QUESTIONS[i].second[0] + "\n");
        printWithDelay(QUESTIONS[i].second[1] + "\n");

        int choice;
        while (true) {
            std::cout << "請輸入選項（1 或 2）：";
            std::cin >> choice;

            if (std::cin.fail() || (choice != 1 && choice != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "無效輸入，請重新輸入。\n";
            }
            else {
                break;
            }
        }
        answers.push_back(choice);
        std::cout << "\n";
    }

    std::string playerMBTI = calculateMBTI(answers);
    printWithDelay("您的 MBTI 類型是：" + playerMBTI + "\n");

    if (playerMBTI == targetMBTI) {
        printWithDelay("恭喜您！人格守衛認可您，您可以通過！\n");
    }
    else {
        printWithDelay("很遺憾，您未能滿足人格守衛的需求！人格守衛對您造成 100 點傷害！\n");
        target.takeDamage(100);
    }
}
