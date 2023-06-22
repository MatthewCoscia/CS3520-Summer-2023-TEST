#include <iostream>
#include <cstring>

using namespace std;

struct planet {
    char* planet_name;
    double planet_distance;
    struct {
        char galaxy_system[13];
        double mass;
    } facts, *facts_ptr = &facts;
} planet_record, *planet_ptr = &planet_record, all_records[5];

/**
 *  // initialize data
    char planet_name[] = "Earth";
    planet_record.planet_name = new char[strlen(planet_name) + 1];
    strcpy(planet_record.planet_name, planet_name);
    planet_record.planet_distance = 149.6;
    strcpy(planet_record.facts.galaxy_system, "Milky Way");
    planet_record.facts.mass = 5.97;

    // print results
    cout << planet_record.planet_name << endl;
    cout << planet_ptr->planet_name << endl;
    cout << planet_record.planet_distance << endl;
    cout << planet_ptr->planet_distance << endl;
    cout << planet_record.facts.mass << endl;
    cout << planet_ptr->facts_ptr->mass << endl;
    cout << planet_record.facts.galaxy_system << endl;
    cout << planet_ptr->facts_ptr->galaxy_system << endl;
 */

int main() {
    char planet_names[5][20] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter" };
    double planet_distances[5] = { 0.39, 0.72, 1.00, 1.52, 5.20 };
    char galaxy_systems[5][13] = { "Solar System", "Solar System", "Milky Way", "Solar System", "Solar System" };
    double masses[5] = { 0.055, 0.815, 5.97, 0.107, 318.0 };

    for (int i = 0; i < 5; i++) {
        all_records[i].planet_name = new char[strlen(planet_names[i]) + 1];
        strcpy(all_records[i].planet_name, planet_names[i]);
        all_records[i].planet_distance = planet_distances[i];
        strcpy(all_records[i].facts.galaxy_system, galaxy_systems[i]);
        all_records[i].facts.mass = masses[i];
        all_records[i].facts_ptr = &(all_records[i].facts);
    }

    // Print all_records
    for (int i = 0; i < 5; i++) {
        std::cout << "Planet Name: " << all_records[i].planet_name << std::endl;
        std::cout << "Planet Distance: " << all_records[i].planet_distance << std::endl;
        std::cout << "Galaxy System: " << all_records[i].facts.galaxy_system << std::endl;
        std::cout << "Mass: " << all_records[i].facts.mass << std::endl;
        std::cout << std::endl;
    }

    // Create a pointer to a dynamically allocated array of records
    struct planet* records_ptr = new planet[5];

    char planet_names_ptr[5][20] = { "Saturn", "Uranus", "Neptune", "Pluto", "Moon" };
    double planet_distances_ptr[5] = { 9.58, 19.18, 30.07, 39.48, 20.52 };
    char galaxy_systems_ptr[5][13] = { "Solar System", "Solar System", "Solar System", "Solar System", "Solar System" };
    double masses_ptr[5] = { 95.2, 14.5, 17.1, 0.00218, 0.0215 };

    for (int i = 0; i < 5; i++) {
        records_ptr[i].planet_name = new char[strlen(planet_names_ptr[i]) + 1];
        strcpy(records_ptr[i].planet_name, planet_names_ptr[i]);
        records_ptr[i].planet_distance = planet_distances_ptr[i];
        strcpy(records_ptr[i].facts.galaxy_system, galaxy_systems_ptr[i]);
        records_ptr[i].facts.mass = masses_ptr[i];
        records_ptr[i].facts_ptr = &(records_ptr[i].facts);
        std::cout << "Planet Name: " << records_ptr[i].planet_name << std::endl;
        std::cout << "Planet Distance: " << records_ptr[i].planet_distance << std::endl;
        std::cout << "Galaxy System: " << records_ptr[i].facts.galaxy_system << std::endl;
        std::cout << "Mass: " << records_ptr[i].facts.mass << std::endl;
        std::cout << std::endl;
    }
}
