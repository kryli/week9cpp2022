#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>

//     Main task - to implement the function fillCountries to put countries into a container]
// (vector<Country> or map<std::string, Country>).

//     Intermediate steps:
//     1. Define operator < for both Cities and Countries based on their names.
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
    std::vector<City> city;

    bool operator==(const Country& right)
    {
        return name == right.name;
    }

    bool operator==(const std::string& right)
    {
        return name == right;
    }

    bool operator!=(const Country& right)
    {
        return !(*this == right);
    } 

};



void fillCountries(std::istream& inFile, std::vector<Country>& countries)
{
    std::string line;
    std::getline (inFile, line);

    while (!inFile.eof())
    {
        std::getline(inFile, line);
        std::stringstream ss(line);
        std::string city, country;
        double lon, lat;
        int pop;
        std::string cell;

        for (int i = 0; i < 5; i++)
        {
            std::getline(ss, cell, ',');

            switch(i)
            {
                case 0: 
                    city = cell; 
                    break;
                case 1:
                    lat = std::stod(cell);
                    break; 
                case 2:
                    lon = std::stod(cell);
                    break;
                case 3:
                    country = cell;
                    break;
                case 4:
                    pop = std::stoi(cell);
                    break;
            }
        }
        Coordinate coor{lon, lat};
        City c{city, coor, pop};
        bool falg = false;

        // for (Country& i : countries)
        // {
        //     if (i == country)
        //     {
        //         i.city.push_back(c); 
        //         falg = true;
        //         break;
        //     }
        // }

        std::vector<Country>::iterator it = std::find(countries.begin(), countries.end(), country);

        if (it != countries.end())
            it->city.push_back(c);
        else
            countries.push_back({country, {c}});
    }
}

int main()
{
    const std::string FILENAME = "../../../data/problem1_cities/cities.csv";
    std::ifstream inputFile;
    std::vector<Country> countries;
    inputFile.open(FILENAME);
    if(inputFile)
    {
        std::cout<<"OK\n";
    }

    fillCountries(inputFile, countries);

    for (const Country& i : countries)
    {
        std::cout << i.name << " : "; 
        for (const City& j : i.city)
            std::cout << j.name << ", ";
        std:: cout << std::endl;
    }
    return 0;
}


