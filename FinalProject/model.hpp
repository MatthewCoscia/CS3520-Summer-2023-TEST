//
// Created by matthewcoscia on 6/26/23.
//

#ifndef FINALPROJECT_MODEL_HPP
#define FINALPROJECT_MODEL_HPP
#include "classes.hpp"
void signIn(std::string username, std::string password);
void signUp(std::string username, std::string password, std::string role);
void checkReservations(std::string username);
int reservationCount(std::string username);
void makeReservation(std::string username, std::string day, std::string time, std::string court);
void deleteReservation(std::string username, std::string day, std::string time, std::string court);
void cancelLesson(std::string username, std::string day, std::string time, std::string court);
void checkCoachingReservations(std::string username);
void createLesson(std::string username, std::string day, std::string time, std::string court);
extern User* user;
void printSchedule();

#endif //FINALPROJECT_MODEL_HPP
