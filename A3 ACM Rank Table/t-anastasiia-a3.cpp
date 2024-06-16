#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Team {
    int teamNumber, solvedProblems, totalPenaltyTime;
    int penaltyTimes[21]; // Максимальное количество задач может быть, например, 20
};

struct Submission {
    int teamNumber, problemNumber, submissionTime, result;
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int C, N; // C - количество команд, N - количество посылок
    cin >> C >> N;

    vector<Team> teams(C + 1);
    for (int i = 1; i <= C; ++i) {
        teams[i].teamNumber = i;
        teams[i].solvedProblems = 0;
        teams[i].totalPenaltyTime = 0;
        memset(teams[i].penaltyTimes, 0, sizeof(teams[i].penaltyTimes));
    }

    vector<Submission> submissions(N);
    for (int i = 0; i < N; ++i) {
        cin >> submissions[i].teamNumber >> submissions[i].problemNumber >> submissions[i].submissionTime >> submissions[i].result;
    }

    sort(submissions.begin(), submissions.end(), [](const Submission& a, const Submission& b) {
        return a.submissionTime < b.submissionTime;
    });

    for (const auto& s : submissions) {
        Team& team = teams[s.teamNumber];
        if (s.result == 1) { // Проверка, принята ли задача
            if (team.penaltyTimes[s.problemNumber] != -1) {
                team.totalPenaltyTime += s.submissionTime + team.penaltyTimes[s.problemNumber] * 20 * 60;
                team.solvedProblems++;
                team.penaltyTimes[s.problemNumber] = -1; // Задача решена, больше не считаем попытки
            }
        } else {
            if (team.penaltyTimes[s.problemNumber] != -1) {
                team.penaltyTimes[s.problemNumber]++;
            }
        }
    }

    sort(teams.begin() + 1, teams.end(), [](const Team& a, const Team& b) {
        if (a.solvedProblems != b.solvedProblems)
            return a.solvedProblems > b.solvedProblems;
        else if (a.totalPenaltyTime != b.totalPenaltyTime)
            return a.totalPenaltyTime < b.totalPenaltyTime;
        else
            return a.teamNumber < b.teamNumber;
    });

    for (int i = 1; i <= C; ++i) {
        if (i > 1) cout << " ";
        cout << teams[i].teamNumber;
    }
    cout << endl;

    return 0;
}
