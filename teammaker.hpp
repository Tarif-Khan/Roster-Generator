#ifndef TEAMMAKER_HPP
#define TEAMMAKER_HPP

#include <string>
#include <vector>
#include <map>
#include <set>

struct Student {
    std::string username;
    std::string programming;
    std::string debugging;
    std::string algorithms;
    std::set<std::string> dontWantToWorkWith;
    std::set<std::string> wantToWorkWith;
};

void readRosterFile(const std::string& filename, std::vector<Student>& students);
void formTeams(const std::vector<Student>& students, int teamSize, bool preferStudentChoice, std::vector<std::vector<std::string>>& teams);
void writeTeamsToFile(const std::vector<std::vector<std::string>>& teams, const std::string& filename);
void printTeamScores(const std::vector<std::vector<std::string>>& teams, const std::map<std::string, Student>& studentMap);

#endif