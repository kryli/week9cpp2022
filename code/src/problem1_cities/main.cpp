#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>

//     Main task - to implement the function fillCountries to put countries into a container]
// (vector<Country> or map<std::string, Country>).

//     Intermediate steps:
//     1. Define operator< for both Cities and Countries based on their names.
//     2. Read cities as pairs <City, name of the country>.
//     3. Use the name of the country to find if there is such country in the container.
//     4. Add a country to the container or a city to an existing country.

struct Coordinate
{
    double longitude;
    double latitude;
};

struct City
{
    std::string name;
    Coordinate coordinate;
    int population;
};

struct Country
{
    std::string name;
    std::vector<City> cities;
    bool operator==(const std::string& r)
    {
        return name == r;
    }
    bool operator==(const Country& r)
    {
        return name == r.name;

    }
};



void fillCountries(std::istream& inFile, std::vector<Country>& countries)
{
    std::string line;
    std::getline(inFile, line);

    while (!inFile.eof())
    {
        std::getline(inFile, line);
        std::stringstream ss(line);
        std::string city,country;
        double longitude, latitude;
        int population;
        for(int i =0; i < 5; i++)
        {
            std::string cell;
            std::getline(ss, cell, ',');
            switch (i)
            {
            case 0:
                city = cell;
                break;
            case 1:
                latitude = std::stod (cell);
                break;
            case 2:
                longitude = std::stod (cell);
                break;
            case 3:
                country = cell;
                break;
            case 4:
                population = std::stoi(cell);
                break;
            default:
                break;
            }

        }
        Coordinate crd{longitude, latitude};
        City cit{city, crd, population};
        Country c{country,{cit}};
        // bool isInVector = 0;
        // for(Country& i :countries)
        // {
        //     if (country == i.name)
        //     {
        //         i.cities.push_back(cit);
        //         isInVector = 1;
        //         break;
        //     }

        // }
        // if(!isInVector)
        //     countries.push_back(c);

       std::vector<Country>::iterator it = std::find (countries.begin(), countries.end(), country);
       if (it == countries.end())
           countries.push_back(c);
        else
            it->cities.push_back(cit);
        

    
    }
    
}

int main()
{
    const std::string FILENAME = "../../../data/problem1_cities/cities.csv";
    std::ifstream inputFile;
    inputFile.open(FILENAME);
    if(inputFile)
    {
        std::cout<<"OK\n";
    }
    std::vector<Country> countries;
    Coordinate c{0,0};
    // Country ct{"Russia", {{"Irkutsk",{0,0}, 0}}};

    fillCountries(inputFile, countries);
    for (const Country& i : countries)
    {
        std::cout << i.name << ':';
        for(const City& j : i.cities)
            std::cout << j.name << '\t';
        std::cout << '\n';
    }
    return 0;
    
}
