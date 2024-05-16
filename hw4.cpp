#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "strutils.cpp"

using namespace std;

struct WeatherData 
{
        string date;
        double temperature;
        double precipitation;
};

WeatherData parseLine(const string& line); 
//Parses a single line of the weather data file into a WeatherData structure

double averageTemperature(const vector<WeatherData>& data); 
//Calculates and returns the average temperature from the loaded data

double totalPrecipitation(const vector<WeatherData>& data); 
//Calculates the total precipitation from the data

WeatherData findExtremesTemperature(const vector<WeatherData>& data, bool findMax); 
//Determines the hottest or coldest day depending on the function findMax argument

WeatherData maxPrecipitation(const vector<WeatherData>& data);
//Identifies the day with the maximum precipitation.

int countDryDays(const vector<WeatherData>& data);
//Counts days with zero precipitation

string getFormattedDate(const string& date);
/*
Converts a date string
from YYYY-MM-DD to a more readable format. For example;
May 15, 2024 . You can implement and use the following months
array to find your month;
const string months[] = { "January", "February", "March",
"April", "May", "June", "July", "August", "September",
"October", "November", "December" }
*/




int main() 
{

    vector<WeatherData> data;

    cout << "Welcome to the Weather Data Analysis Program!" << endl
    << "1. Load data file" << endl 
    << "2. Display average temperature" << endl
    << "3. Display total precipitation" << endl
    << "4. Display the number of dry days" << endl
    << "5. Display the hottest day" << endl
    << "6. Display the coldest day" << endl
    << "7. Display the day with the highest precipitation" << endl
    << "8. Close the program" << endl
    << "" << endl;

    int opt = 0;
    bool checkDataLoaded = false;
    while(opt != 8) 
    {
        cout << "Choose an option: ";
        cin >> opt;

        if(opt == 1) 
        {
            ifstream input;
            string filename;
            cout << "Enter the file name: ";
            cin >> filename;
            input.open(filename.c_str());
            if(input.fail()) 
            {
                cout << "Cannot open the file!" << endl;
                continue;
            }
            else 
            {
                string s;
                WeatherData d;
                while(getline(input, s)) 
                {
                    d = parseLine(s);
                    data.push_back(d);
                }
                cout << "Data loaded successfully." << endl;
                checkDataLoaded = true;
            }
        }
        else if(opt == 2)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                double avgTemp = averageTemperature(data);
                cout << "Average Temperature: " << avgTemp << " Celsius" << endl;
                continue;
            }
        }
        else if(opt == 3)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                double totalPrec = totalPrecipitation(data);
                cout << "Total Precipitation: " << totalPrec << " mm" << endl;
                continue;
            }
        }
        else if(opt == 4)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                int dryDays = countDryDays(data);
                cout << "Number of Dry Days: " << dryDays << endl;
            }
        }
        else if(opt == 5)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                WeatherData hottestDay = findExtremesTemperature(data, true);
                string date = getFormattedDate(hottestDay.date);
                cout << "Hottest Day: " << date << " with " << hottestDay.temperature  << " Celsius" << endl;
            }
        }
        else if(opt == 6)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                WeatherData coldestDay = findExtremesTemperature(data, false);
                string date = getFormattedDate(coldestDay.date);
                cout << "Coldest Day: " << date << " with " << coldestDay.temperature  << " Celsius" << endl;
            }
        }
        else if(opt == 7)
        {
            if(!checkDataLoaded)
            {
                cout << "Please load a data file first." << endl;
                continue;
            }
            else
            {
                WeatherData maxPrecDate = maxPrecipitation(data);
                string date = getFormattedDate(maxPrecDate.date);
                cout << "Highest Precipitation Day: " << date << " with " << maxPrecDate.precipitation  << " mm" << endl;
            }
        }
        else if(opt == 8)
        {
            cout << "Exiting program..." << endl;
            return 0;
        }
        else
        {
            cout << "Invalid option. Please enter a valid option." << endl;
            continue;
        }

    }
    return 0;
}

WeatherData parseLine(const string& line)
{
    WeatherData d;
    istringstream input(line);
    string date, temperature, precipitation;
    input >> date >> temperature >> precipitation;
    d.date = date.erase(date.length() - 1);
    d.temperature = atof(temperature);
    d.precipitation = atof(precipitation);
    return d;
 
}

double averageTemperature(const vector<WeatherData>& data)
{
    double sum = 0, avg;
    for(int i = 0; i < data.size(); i++)
    {
        sum += data[i].temperature;
    }
    return sum / data.size();
}

double totalPrecipitation(const vector<WeatherData>& data)
{
    double sum = 0;
    for(int i = 0; i < data.size(); i++)
    {
        sum += data[i].precipitation;
    }
    return sum;
}

int countDryDays(const vector<WeatherData>& data)
{
    int cnt = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i].precipitation == 0)
        {
            cnt++;
        }
    }

    return cnt;
}

WeatherData findExtremesTemperature(const vector<WeatherData>& data, bool findMax)
{
    //display hottest day if findMax => true
    if(findMax)
    {
        double maxVal = data[0].temperature;
        for(int i = 0; i < data.size(); i++)
        {
            if(maxVal < data[i].temperature)
            {
                maxVal = data[i].temperature;
            }
        }
        for(int i = 0; i < data.size(); i++)
        {
            if(maxVal == data[i].temperature)
            {
                return data[i];
            }
        }
    }
    else
    {
        double minVal = data[0].temperature;
        for(int i = 0; i < data.size(); i++)
        {
            if(minVal > data[i].temperature)
            {
                minVal = data[i].temperature;
            }
        }
        for(int i = 0; i < data.size(); i++)
        {
            if(minVal == data[i].temperature)
            {
                return data[i];
            }
        }
        
    }
}

WeatherData maxPrecipitation(const vector<WeatherData>& data)
{
    double maxVal = data[0].precipitation;
        for(int i = 0; i < data.size(); i++)
        {
            if(maxVal < data[i].precipitation)
            {
                maxVal = data[i].precipitation;
            }
        }
        for(int i = 0; i < data.size(); i++)
        {
            if(maxVal == data[i].precipitation)
            {
                return data[i];
            }
        }
}

string getFormattedDate(const string& date)
{
    const string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    int monthNum = atoi(date.substr(5, 2));
    string month = months[monthNum -1];
    string day = date.substr(8, 2);
    string year = date.substr(0, 4);
    string formattedDate = month + " " + day + ", " + year;
    return formattedDate;
}

