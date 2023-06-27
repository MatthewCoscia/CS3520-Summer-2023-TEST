//
// Created by matthewcoscia on 6/26/23.
//

#ifndef FINALPROJECT_CLASSES_HPP
#define FINALPROJECT_CLASSES_HPP

#include <string>
#include <map>

class Reservation {
public:
    std::string day;
    std::string time;
    std::string court;
    std::string reservedBy;
    Reservation(const std::string& day, const std::string& time,
                const std::string& court, const std::string& reservedBy);
    Reservation();
    void print();
};

class User {
public:
    std::string username;
    std::string membership;
    bool signedIn = false;
    virtual std::string getSymbol() = 0;
    virtual void setSkillLevel(char skill) = 0;
    virtual std::string getSkillLevel() = 0;
    virtual ~User() {}
};

class ClubMember : public User {
public:
    char skillLevel;
    void setSkillLevel(char skill) override;
    std::string getSkillLevel() override;
    std::string symbol = "CM";
    std::string getSymbol() override;
};

class ClubOfficer : public User {
public:
    std::string symbol = "CO";
    void setSkillLevel(char skill) override;
    std::string getSkillLevel() override;
    std::string getSymbol() override;
};

class ClubCoach : public User {
public:
    std::string symbol = "CC";
    void setSkillLevel(char skill) override;
    std::string getSkillLevel() override;
    std::string getSymbol() override;
};

class Empty : public User {
    std::string symbol = "X";
    void setSkillLevel(char skill) override;
    std::string getSkillLevel() override;
    std::string getSymbol() override;
};

#endif //FINALPROJECT_CLASSES_HPP
