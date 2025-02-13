# Dream Adventure

## 🏆 Project Overview
**Dream Adventure** is a C++ fantasy adventure game where players enter a dream world filled with unpredictable challenges. Players must battle three distinct monsters, each presenting a unique gameplay mechanic. Every playthrough introduces randomized monster encounters, adding to the game's replayability and mystery.

---

## 🎮 Gameplay
### 1. Personality Guardian (MBTI Test)
- Players answer a series of personality-based questions.
- The guardian seeks a specific MBTI type, and players must attempt to match it.
- If successful, the player passes; if not, they are eliminated.

### 2. Dictionary Beast (Typing Challenge)
- Players unscramble jumbled words within a time limit.
- Words increase in difficulty across three rounds.
- Success leads to victory; failure ends the game.

### 3. Code Shadow (Password Guessing Game)
- Players guess a randomly generated numeric password.
- Hints like "1A2B" guide them towards the correct answer.
- Players have 10 attempts to crack the code before the game ends.

---

## 🛠️ System Design
### Class Structure
├── Player.h/.cpp         # Defines player attributes and interactions
├── Enemy.h               # Base class for all enemies
├── Guardian.h/.cpp       # Personality Guardian class (MBTI Challenge)
├── DictionaryBeast.h/.cpp # Dictionary Beast class (Typing Challenge)
├── CodeShadow.h/.cpp     # Code Shadow class (Password Challenge)
├── main.cpp              # Game entry point
### Key Design Patterns
- **Inheritance & Polymorphism:**
  - `Enemy` serves as the base class, with `Guardian`, `DictionaryBeast`, and `CodeShadow` inheriting its behavior.
- **File I/O:**
  - `DictionaryBeast` loads words from `wordlist.txt` for randomized challenges.
- **Exception Handling:**
  - Prevents crashes from file errors or invalid input.
- **Memory Management:**
  - Uses `std::unique_ptr` to avoid memory leaks.
- **Randomization:**
  - `std::shuffle` ensures enemies appear in a random order.

---

## 🚀 Getting Started
### Prerequisites
- C++ compiler

### Installation & Compilation
```bash
# Clone the repository
git clone https://github.com/yourusername/Dream-Adventure.git
cd Dream-Adventure

# Compile using g++
g++ -std=c++17 main.cpp Player.cpp Guardian.cpp DictionaryBeast.cpp CodeShadow.cpp -o dream_adventure

# Run the game
./dream_adventure

---

## 🤝 Contributors
- Tsai, Ping-Yun
- Chen, Guan-You
- Su, Yi-Hsuan
