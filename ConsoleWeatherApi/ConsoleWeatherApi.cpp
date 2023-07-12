#include <iostream>
#include "WeatherApiClient.h"
#include "DegreeEnums.h"
#include "WeatherInfo.h"
#include "WeatherApiClient.cpp"
#include "WeatherInfo.cpp"

bool checksIfText(std::string text) {
    for (char c : text) {
        if (isalpha(c) == false) {
            return false;
            break;
        }
    }

    return true;
}

int main()
{
    std::string apiKey;
    std::string cityName;
    std::string degreeName;
    Degree degree;

    bool validInput = false;

    std::cout << "Enter your API Key: ";
    std::cin >> apiKey;

    std::cout << "Which degree type? Celcius, Fahrenheit, Kelvin? ";
    std::cin >> degreeName;

    std::transform(degreeName.begin(), degreeName.end(), degreeName.begin(),
        [](unsigned char c) { return std::tolower(c); });

    switch (degreeName[0]) {
    case 'c':
        degree = Celcius;
        break;
    case 'k':
        degree = Kelvin;
        break;
    case 'f':
        degree = Fahrenheit;
        break;
    }

    WeatherApiClient weatherApiClient(apiKey);

    while (validInput == false) {
        std::cout << "Enter your requested city: ";
        std::cin >> cityName;

        bool isText = true;
        isText = checksIfText(cityName);

        if (isText) {
            validInput = true;
        }
        else {
            std::cout << "Invalid Input. Please enter a valid city name \n";
            std::cin.clear();
        }
    }

    std::string jsonResponse = weatherApiClient.getWeather(cityName);

    json jsonData = json::parse(jsonResponse);

    WeatherInfo weatherInfo(jsonData);

    weatherInfo.printWeatherValues(weatherInfo, degree);
}
