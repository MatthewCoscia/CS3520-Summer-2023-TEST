//
// Created by matthewcoscia on 6/26/23.
//

#include "classes.hpp"
#include <iostream>

std::string ClubMember::getSymbol() {
    return symbol;
}

std::string ClubCoach::getSymbol() {
    return symbol;
}

std::string ClubOfficer::getSymbol() {
    return symbol;
}

std::string Empty::getSymbol() {
    return symbol;
}

// Constructor definition
Reservation::Reservation(const std::string& day, const std::string& time,
                         const std::string& court, const std::string& reservedBy)
        : day(day), time(time), court(court), reservedBy(reservedBy) {
    // Additional initialization or validation if needed
}

Reservation::Reservation() {}

void Reservation::print() {
    std::cout << "{ " << day << ", " << time << ", " << court << ", " << reservedBy << " }" << std::endl;
}

void ClubMember::setSkillLevel(char skill) {
    skillLevel = skill;
}

void ClubCoach::setSkillLevel(char skill) {}

void ClubOfficer::setSkillLevel(char skill) {}

void Empty::setSkillLevel(char skill) {}
