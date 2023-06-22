#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Maze_Point {
public:
    int x;
    int y;
    void Maze_Point_Constructor(int y, int x);
    void print();
};

void Maze_Point :: Maze_Point_Constructor(int y, int x) {
    this->x = x;
    this->y = y;
}

void Maze_Point :: print() {
    cout << "(" << this->x << ", " << this->y << ")";
}

class MazeGenerator {
public:
    int size;
    vector<vector<string>> data;
    void generateMaze(int size);
    void print();
};

void MazeGenerator::print() {
    for (int i = 0; i < this->size; ++i) {
        for (int k = 0; k < this->size; ++k) {
            cout << this->data[i][k] << " ";
        }
        cout << "\n";
    }
}

vector<Maze_Point> generate_path(Maze_Point start, Maze_Point end, int size) {
    vector<Maze_Point> path;
    path.push_back(start);
    Maze_Point pos1;
    pos1.Maze_Point_Constructor(start.y, 1);
    path.push_back(pos1);
    pos1.print();
    cout << "\n";
    int ender = 0;
    while (ender != 1) {
        Maze_Point temp = path[path.size() - 1];
        vector<Maze_Point> possibleOptions;
        if (temp.x + 1 < size - 1) {
            Maze_Point p1;
            p1.Maze_Point_Constructor(temp.y, temp.x + 1);
            possibleOptions.push_back(p1);
        }
        if (temp.x - 1 > 0) {
            Maze_Point p1;
            p1.Maze_Point_Constructor(temp.y, temp.x - 1);
            possibleOptions.push_back(p1);
        }
        if (temp.y - 1 > 0) {
            Maze_Point p1;
            p1.Maze_Point_Constructor(temp.y - 1, temp.x);
            possibleOptions.push_back(p1);
        }
        if (temp.y + 1 < size - 1) {
            Maze_Point p1;
            p1.Maze_Point_Constructor(temp.y + 1, temp.x);
            possibleOptions.push_back(p1);
        }
        vector<Maze_Point> finalPossibleOptions;
        bool isFinal = false;
        for (int i = 0; i < possibleOptions.size(); ++i) {
            if (possibleOptions[i].x == end.x && possibleOptions[i].y == end.y) {
                isFinal = true;
                ender = 1;
                break;
            }
        }
        if (isFinal) {
            path.push_back(end);
            break;
        }
        for (int i = 0; i < possibleOptions.size(); ++i) {
            bool used = false;
            for (int k = 0; k < path.size(); ++k) {
                if (possibleOptions[i].x == path[k].x && possibleOptions[i].y == path[k].y) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                finalPossibleOptions.push_back(possibleOptions[i]);
            }
        }
        random_shuffle(finalPossibleOptions.begin(), finalPossibleOptions.end());
        path.push_back(finalPossibleOptions[0]);
        possibleOptions = vector<Maze_Point>();
        finalPossibleOptions = vector<Maze_Point>();
     }
    return path;
}

void MazeGenerator::generateMaze(int size) {
    vector<Maze_Point> points;
    this->size = size;
    for (int i = 0; i < size; ++i) {
        vector<string> temp;
        for (int k = 0; k < size; ++k) {
            temp.push_back("#");
        }
        this->data.push_back(temp);
        temp = vector<string>();
    }
    srand(time(0));
    int start = 2 + rand() % size - 2;
    int end = 1 + rand() % size - 2;
    Maze_Point start_coords;
    start_coords.Maze_Point_Constructor(start, 0);
    this->data[end][size - 1] = ".";
    Maze_Point end_coords;
    end_coords.Maze_Point_Constructor(end, size - 2);
    vector<Maze_Point> path = generate_path(start_coords, end_coords, start);
    for (int i = 0; i < path.size(); ++i) {
        this->data[path[i].y][path[i].x] = ".";
    }
}

int Maze() {
    MazeGenerator maze = MazeGenerator();
    maze.generateMaze(4);
    maze.print();
}

