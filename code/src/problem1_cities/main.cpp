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
    bool operator!=(const Country& r)
    {
        return !(*this == r);
    }
};

std::ostream& operator<<(std::ostream& stream, const Country& country)
{
    stream << country.name << ": ";
    for (const City& j: country.cities)
        stream << j.name << '\t';
    return stream;
}

void fillCountries(std::istream& inFile, std::vector<Country>& countries)
{
    std::string line;
    std::getline(inFile, line);
    while (!inFile.eof())
    {
        std::getline(inFile, line);
        std::stringstream buff(line);
        std::string city, country;
        double lot, lat;
        int pop;
        for (int i = 0; i < 5; ++i)
        {
            std::string cell;
            std::getline(buff, cell, ',');
            switch (i)
            {
                case 0:
                    city = cell;
                    break;
                case 1:
                    lat = std::stod(cell);
                    break;
                case 2:
                    lot = std::stod(cell);
                    break;
                case 3:
                    country = cell;
                    break;
                case 4:
                    pop = std::stoi(cell);
                    break;
            }


        }
        City ca{city, {lot, lat}, pop};
        std::vector<Country> :: iterator it = std::find(countries.begin(), countries.end(), country);
        if (it == countries.end())
            countries.push_back({country, {ca}});
        else
            it->cities.push_back(ca);
        // bool isInCountries = false;
        // for (Country& i: countries)
        // {
        //     if (i == country)
        //     {
        //         i.cities.push_back(ca);
        //         isInCountries = true;
        //         break;
        //     }
        // }
        // if (!isInCountries)
        // {
        //     countries.push_back({country, {ca}});
        // }
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
    fillCountries(inputFile, countries);
    Coordinate x{1.1, 2.2};
    City y{"Moscow", x, 1000000000};
    for (const Country& i: countries)
    {
        std::cout << i << '\n';
        // std::cout << i.name << ": ";
        // for (const City& j: i.cities)
        // {
        //     std::cout << j.name << '\t';
        // }
    }
    return 0;
}
