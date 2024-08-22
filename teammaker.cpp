#include "teammaker.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void readRosterFile(const std::string& filename, std::vector<Student>& students) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string field;

        Student student;
        std::getline(iss, student.username, ',');
        std::getline(iss, student.programming, ',');
        std::getline(iss, student.debugging, ',');
        std::getline(iss, student.algorithms, ',');

        std::string dontWantToWorkWith;
        std::getline(iss, dontWantToWorkWith, ',');
        std::istringstream dontWantToWorkWithIss(dontWantToWorkWith);
        std::string username;
        while (std::getline(dontWantToWorkWithIss, username, ';')) {
            student.dontWantToWorkWith.insert(username);
        }

        std::string wantToWorkWith;
        std::getline(iss, wantToWorkWith, ',');
        std::istringstream wantToWorkWithIss(wantToWorkWith);
        while (std::getline(wantToWorkWithIss, username, ';')) {
            student.wantToWorkWith.insert(username);
        }

        students.push_back(student);
    }
}

void formTeams(const std::vector<Student>& students, int teamSize, bool preferStudentChoice, std::vector<std::vector<std::string>>& teams) {
    std::map<std::string, Student> studentMap;
    for (const auto& student : students) {
        studentMap[student.username] = student;
    }

    std::set<std::string> assignedStudents;
    for (const auto& student : students) {
        if (assignedStudents.count(student.username) > 0) {
            continue;
        }

        std::vector<std::string> team;
        team.push_back(student.username);
        assignedStudents.insert(student.username);

        if (preferStudentChoice) {
            for (const auto& username : student.wantToWorkWith) {
                if (assignedStudents.count(username) == 0 && studentMap.count(username) > 0 && static_cast<int>(team.size()) < teamSize) {
                    team.push_back(username);
                    assignedStudents.insert(username);
                }
            }
        }

        while (static_cast<int>(team.size()) < teamSize) {
            for (const auto& otherStudent : students) {
                if (assignedStudents.count(otherStudent.username) == 0 &&
                    student.dontWantToWorkWith.count(otherStudent.username) == 0 &&
                    static_cast<int>(team.size()) < teamSize) {
                    team.push_back(otherStudent.username);
                    assignedStudents.insert(otherStudent.username);
                }
            }
        }

        teams.push_back(team);
    }
}

void writeTeamsToFile(const std::vector<std::vector<std::string>>& teams, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < teams.size(); ++i) {
        file << i + 1;
        for (const auto& username : teams[i]) {
            file << "," << username;
        }
        file << std::endl;
    }
}

void printTeamScores(const std::vector<std::vector<std::string>>& teams, const std::map<std::string, Student>& studentMap) {
    std::cout << "Team Scores:" << std::endl;
    for (size_t i = 0; i < teams.size(); ++i) {
        int programmingScore = 0;
        int debuggingScore = 0;
        int algorithmsScore = 0;

        for (const auto& username : teams[i]) {
            const auto& student = studentMap.at(username);
            if (student.programming == "Advanced") {
                programmingScore += 3;
            } else if (student.programming == "Intermediate") {
                programmingScore += 2;
            } else if (student.programming == "Beginner") {
                programmingScore += 1;
            }

            if (student.debugging == "Advanced") {
                debuggingScore += 3;
            } else if (student.debugging == "Intermediate") {
                debuggingScore += 2;
            } else if (student.debugging == "Beginner") {
                debuggingScore += 1;
            }

            if (student.algorithms == "Advanced") {
                algorithmsScore += 3;
            } else if (student.algorithms == "Intermediate") {
                algorithmsScore += 2;
            } else if (student.algorithms == "Beginner") {
                algorithmsScore += 1;
            }
        }

        std::cout << "Team " << i + 1 << ": " << programmingScore << " " << debuggingScore << " " << algorithmsScore << std::endl;
    }
}