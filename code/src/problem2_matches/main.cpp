#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

class FootballTeam
{
public:
    FootballTeam(string name, string city, string stadium, double level) : _name(name), _city(city), _stadium(stadium),
     _level(level), _points(0), _wins(0), _draws(0), _losses(0) {}

    string getName() const
    {
        return _name;
    }
    string getCity() const
    {
        return _city;
    }
    string getStadium() const
    {
        return _stadium;
    }
    double getLevel() const
    {
        return _level;
    }
    int getPoints() const { return _points; }
    void addWin() { _wins++; }
    void addDraw() { _draws++; }
    void addLoss() { _losses++; }
    void setPoints(int points) { _points+= points; }

private:
    string _name, _city, _stadium;
    double _level;
    int _points, _wins, _draws, _losses;
};

class Tournament
{
public:
    Tournament(vector<FootballTeam> teams = {}) : _teams(teams), _round(0) {}


    void simulateRound();
    void printTeams()
    {
        for (FootballTeam tm : _teams)
            cout << tm.getName() << '\t' << tm.getCity() << '\n';
    }


private:
    vector<FootballTeam> _teams;
    int _round;
};


class Match
{
public:
    Match(FootballTeam& localTeam, FootballTeam& visitorTeam) :  _localTeam(localTeam),
    _visitorTeam(visitorTeam), _localGoals(0), _visitorGoals(0) {}

    void play()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, ceil( abs(_localTeam.getLevel() - _visitorTeam.getLevel()) ) * 10);
        int newRandomNumber = distr(gen);


    }

private:
    int _localGoals, _visitorGoals;
    FootballTeam& _localTeam, _visitorTeam;

};

void parseLineTeam(const string &line, string &name, string &city, string &stadium, double &level)
{
    size_t posName = line.find(',');
    name = line.substr(0, posName);

    size_t posCity = line.find(',', posName + 1);
    city = line.substr(posName + 1, posCity - posName - 1);

    size_t posStadium = line.find(',', posCity + 1);
    stadium = line.substr(posCity + 1, posStadium - posCity - 1);

    size_t posLevel = line.size() - 1;
    string levelString = line.substr(posStadium + 1, posLevel - posStadium);
    stringstream ss(levelString);
    ss >> level;
}

void loadTeams(istream &in, vector<FootballTeam> &teams)
{
    string buffer;
    getline(in, buffer);
    while (getline(in, buffer))
    {
        string name;
        string city;
        string stadium;
        double level;
        parseLineTeam(buffer, name, city, stadium, level);
        cout << "name = " << name << "\n";
        cout << "city = " << city << "\n";
        cout << "stadium = " << stadium << "\n";
        cout << "level = " << level << "\n\n";
        teams.push_back(FootballTeam(name, city, stadium, level));
    }
}

int main()
{
    const string FILENAME = "../../../data/problem2_matches/football.csv";
    ifstream inputFile;
    inputFile.open(FILENAME);

    vector<FootballTeam> teams;
    loadTeams(inputFile, teams);
    Tournament tour(teams);
    tour.printTeams();

    return 0;
}
