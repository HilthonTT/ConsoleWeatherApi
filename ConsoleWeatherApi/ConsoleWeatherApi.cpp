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
    std::string apiKey = "291dfb57060691b6978a449d8f5dec05";
    std::string cityName = "";

    bool validInput = false;

    /*std::cout << "Enter your API Key: ";
    std::cin >> apiKey;*/

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

    weatherInfo.printWeatherValues(weatherInfo, Celcius);

}
