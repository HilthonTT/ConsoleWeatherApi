#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class WeatherInfo
{

private:
	std::pair<std::string, double> getDegreeInfo(Degree degree) {
		std::string degreeText;
		double degreeAdjustment;

		switch (degree) {
		case Celcius:
			degreeText = "Celsius";
			degreeAdjustment = 273.15;
			break;
		case Fahrenheit:
			degreeText = "Fahrenheit";
			degreeAdjustment = 459.67;
			break;
		default:
			degreeText = "Kelvin";
			degreeAdjustment = 0;
			break;
		}

		return std::make_pair(degreeText, degreeAdjustment);
	}

public:
	std::string main;
	std::string description;
	double temperature;
	double feelsLike;
	double tempMin;
	double tempMax;
	int pressure;
	int humidity;

	WeatherInfo(const json& jsonData) {
		main = jsonData["weather"][0]["main"];
		description = jsonData["weather"][0]["description"];
		temperature = jsonData["main"]["temp"];
		feelsLike = jsonData["main"]["feels_like"];
		tempMin = jsonData["main"]["temp_min"];
		tempMax = jsonData["main"]["temp_max"];
		pressure = jsonData["main"]["pressure"];
		humidity = jsonData["main"]["humidity"];
	}

	void printWeatherValues(WeatherInfo weatherInfo, Degree degree) {
		std::pair<std::string, double> degreeInfo = getDegreeInfo(degree);
		std::string degreeText = degreeInfo.first;
		double degreeAdjustment = degreeInfo.second;

		double convertedTemp = weatherInfo.temperature - degreeAdjustment;
		double convertedFeelsLike = weatherInfo.feelsLike - degreeAdjustment;
		double convertedTempMin = weatherInfo.tempMin - degreeAdjustment;
		double convertedTempMax = weatherInfo.tempMax - degreeAdjustment;

		std::cout << "Main: " << weatherInfo.main << std::endl;
		std::cout << "Description: " << weatherInfo.description << std::endl;
		std::cout << "Temperature: " << convertedTemp << " " << degreeText << std::endl;
		std::cout << "Feels Like: " << convertedFeelsLike << " " << degreeText << std::endl;
		std::cout << "Temperature Min: " << convertedTempMin << " " << degreeText << std::endl;
		std::cout << "Temperature Max: " << convertedTempMax << " " << degreeText << std::endl;
		std::cout << "Pressure: " << weatherInfo.pressure << std::endl;
		std::cout << "Humidity: " << weatherInfo.humidity << std::endl;
	}
};