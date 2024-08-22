#include "teammaker.hpp"
#include <iostream>
#include <limits>

int main() {
    std::string filename;
    std::cout << "Enter the roster file name: ";
    std::cin >> filename;

    std::vector<Student> students;
    readRosterFile(filename, students);

    int teamSize;
    std::cout << "Enter the team size (3 or 4): ";
    std::cin >> teamSize;

    bool preferStudentChoice;
    std::cout << "Do you want to give preference to student choices? (1 for yes, 0 for no): ";
    std::cin >> preferStudentChoice;

    // Clear any remaining characters from the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<std::string>> teams;
    formTeams(students, teamSize, preferStudentChoice, teams);

    writeTeamsToFile(teams, "teams.csv");

    std::map<std::string, Student> studentMap;
    for (const auto& student : students) {
        studentMap[student.username] = student;
    }
    printTeamScores(teams, studentMap);

    return 0;
}