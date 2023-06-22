#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;


class Route {
private:
    string startCity;
    string finalCity;
    int distance;
public:
    Route(string start, string final, int dist) {
        startCity = start;
        finalCity = final;
        distance = dist;
	}

    void print() {
        cout << "{" << startCity << ", " << finalCity << ", " << distance << "}" << "\n";
    }
    string getStartCity() const {
        return startCity;
    }
    string getFinalCity() const {
        return finalCity;
    }
    int getDistance() const {
        return distance;
    }
	
};

map<string, map<string, int>> findShortestKnownDistance(const vector<Route> routeList) {
    map<string, map<string, int>> shortestKnownDistance;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    for (const Route& route : routeList) {
        string startCity = route.getStartCity();
        string finalCity = route.getFinalCity();
        int distance = route.getDistance();

        // Create a priority queue and a map for each city
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        map<string, int> cityDistance;

        pq.push(make_pair(0, startCity));
        while (!pq.empty()) {
            pair<int, string> current = pq.top();
            pq.pop();

            int currentDistance = current.first;
            string currentCity = current.second;

            // If the target is not in cityDistances, update it
            if (cityDistance.find(currentCity) == cityDistance.end()) {
                cityDistance[currentCity] = currentDistance;

                // For all cities directly connected to the target
                // Add Distance(c, d + distance from target to c) to the priority queue
                for (const Route& r : routeList) {
                    if (r.getStartCity() == currentCity) {
                        int distanceToC = currentDistance + r.getDistance();
                        pq.push(make_pair(distanceToC, r.getFinalCity()));
                    }
                }
            }
        }

        // Store the shortest distances for the current city in the main map
        shortestKnownDistance[startCity] = cityDistance;
    }

    return shortestKnownDistance;

}

void printShortestPaths(const map<string, map<string, int>>& shortestKnownDistance) {
    fstream outfile("shortestDistances.txt", ios::out);
    if (!outfile.is_open()) {
        cout << "Failed to open the output file." << endl;
        return;
    }
    for (const auto& entry : shortestKnownDistance) {
        const string& startCity = entry.first;
        const map<string, int>& cityDistances = entry.second;

        for (const auto& cityEntry : cityDistances) {
            const string& finalCity = cityEntry.first;
            int distance = cityEntry.second;
            if (distance != 0) {
                cout << "Path: " << startCity << " to " << finalCity << ", Distance: " << distance << endl;
                outfile << "Path: " << startCity << " to " << finalCity << ", Distance: " << distance << endl;
            }
        }
    }
    outfile.close();
}

	
int main() {
    fstream file("map.txt", ios::in);
    string line;
    vector<string> words;
    string word;
    int tempDist;
    vector<Route> routeList;
    if (file.is_open()) {
        while(getline(file, line)) {
            istringstream iss(line);
            while (iss >> word) {
                words.push_back(word);
            }
            tempDist = stoi(words[2]);
            routeList.push_back(Route(words[0], words[1], tempDist));
            words.clear();
        }
        file.close();
    }
    else {
        cout << "Failed to open the file." << endl;
    }
    map<string, map<string, int>> final = findShortestKnownDistance(routeList);
    printShortestPaths(final);

	return 0;
}
