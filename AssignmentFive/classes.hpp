// animal.h

#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>

class Animal {
protected:
    int xpos;
    int ypos;
    bool moved;
    int starve_count = 0;
    int breed_count = 0;

public:
    virtual char getSymbol() = 0;
    virtual int getXPos() = 0;
    virtual int getYPos() = 0;
    virtual void setPos(int YPos, int XPos) = 0;
    virtual void move() = 0;
    virtual void eat() = 0;
    virtual void createOffspring() = 0;
    virtual void checkIfFertilized() = 0;
    virtual ~Animal() {}
    void changeMoved(bool movedLocal);
    void setStarve();
    void setBreed();
    void increaseBreed();
    int getStarvedInt();
    void increaseStarved();
};

class Queen : public Animal {
private:
    char symbol = 'Q';
    bool fertilized = false;
    int breed_time_queen = 0;
    int cant_breed_time_queen = 0;
    int breed_cooldown = 0;

public:
    char getSymbol() override;
    int getXPos() override;
    int getYPos() override;
    void setPos(int YPos, int XPos) override;
    void move() override;
    void eat() override;
    void createOffspring() override;
    void checkIfFertilized() override;
    Queen(bool movedLocal);
};

class Worker : public Animal {
private:
    char symbol = 'W';

public:
    char getSymbol() override;
    int getXPos() override;
    int getYPos() override;
    void setPos(int YPos, int XPos) override;
    void move() override;
    void eat() override;
    void createOffspring() override;
    void checkIfFertilized() override;
    Worker(bool movedLocal);
};

class Male_Ant : public Animal {
private:
    char symbol = 'O';

public:
    char getSymbol() override;
    int getXPos() override;
    int getYPos() override;
    void setPos(int YPos, int XPos) override;
    void move() override;
    void eat() override;
    void createOffspring() override;
    void checkIfFertilized() override;
    Male_Ant(bool movedLocal);
};

class Doodlebug : public Animal {
private:
    char symbol = 'X';

public:
    char getSymbol() override;
    int getXPos() override;
    int getYPos() override;
    void setPos(int YPos, int XPos) override;
    void move() override;
    void eat() override;
    void createOffspring() override;
    void checkIfFertilized() override;
    Doodlebug(bool movedLocal);
};

class Empty : public Animal {
private:
    char symbol = ' ';

public:
    char getSymbol() override;
    int getXPos() override;
    int getYPos() override;
    void setPos(int YPos, int XPos) override;
    void move() override;
    void createOffspring() override;
    void checkIfFertilized() override;
    void eat() override;
};

#endif  // ANIMAL_H

