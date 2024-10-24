#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    int correctOption;
};

class Quiz {
private:
    vector<Question> questions;

public:
    Quiz() {
        questions = {
            {"What is the capital of France?", {"1) Berlin", "2) Madrid", "3) Paris", "4) Rome"}, 3},
            {"Which planet is known as the Red Planet?", {"1) Venus", "2) Mars", "3) Jupiter", "4) Saturn"}, 2},
            {"Who wrote '1984'?", {"1) George Orwell", "2) Mark Twain", "3) J.K. Rowling", "4) Ernest Hemingway"}, 1},
            {"What is the largest ocean on Earth?", {"1) Atlantic", "2) Indian", "3) Arctic", "4) Pacific"}, 4},
            {"Which element has the chemical symbol 'O'?", {"1) Gold", "2) Oxygen", "3) Osmium", "4) Silver"}, 2}
        };
    }

    void takeQuiz() {
        int score = 0;
        string name;

        cout << "Enter your name: ";
        getline(cin, name);

        for (const auto& question : questions) {
            cout << question.questionText << endl;
            for (const auto& option : question.options) {
                cout << option << endl;
            }

            int userOption;
            cout << "Enter the correct option number: ";
            cin >> userOption;

            if (userOption == question.correctOption) {
                score++;
            }
        }

        cout << "Your score: " << score << "/" << questions.size() << endl;
        saveScore(name, score);
    }

    void saveScore(const string& name, int newScore) {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("leaderboard.txt");
        bool nameExists = false;

        string line;
        while (getline(leaderboardFile, line)) {
            size_t delimiterPos = line.find(": ");
            string existingName = line.substr(0, delimiterPos);
            int existingScore = stoi(line.substr(delimiterPos + 2));

            if (existingName == name) {
                existingScore = max(existingScore, newScore);
                nameExists = true;
            }
            leaderboardData.push_back({existingName, existingScore});
        }
        leaderboardFile.close();

        if (!nameExists) {
            leaderboardData.push_back({name, newScore});
        }

        ofstream leaderboardOut("leaderboard.txt");
        for (const auto& entry : leaderboardData) {
            leaderboardOut << entry.first << ": " << entry.second << endl;
        }
        leaderboardOut.close();
    }

    void showLeaderboard() const {
        ifstream leaderboard("leaderboard.txt");
        if (!leaderboard.is_open()) {
            cerr << "Error opening leaderboard." << endl;
            return;
        }

        string line;
        cout << "Leaderboard:" << endl;
        while (getline(leaderboard, line)) {
            cout << line << endl;
        }
    }

    void showQuestions() const {
        cout << "Questions in the quiz:\n";
        for (const auto& question : questions) {
            cout << "- " << question.questionText << endl;
        }
    }
};

int main() {
    cout << "Welcome to the Quiz Application!" << endl;

    Quiz quiz;

    while (true) {
        int choice;
        cout << "\n1. Take Quiz\n2. Show Questions\n3. Show Leaderboard\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                quiz.takeQuiz();
                break;
            case 2:
                quiz.showQuestions();
                break;
            case 3:
                quiz.showLeaderboard();
                break;
            case 4:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
