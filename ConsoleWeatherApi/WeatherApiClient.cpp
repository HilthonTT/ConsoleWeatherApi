#include "WeatherApiClient.h"

class WeatherApiClient {
	
private:
	CURL* curl;
	std::string apiKey;

	static size_t WriteCallback(char* data, size_t size, size_t nmemb, std::string* buffer) {
		buffer->append(data, size * nmemb);
		return size * nmemb;
	}

public:
	WeatherApiClient(const std::string& apiKey) : apiKey(apiKey) {
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();
	}

	~WeatherApiClient() {
		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}

	std::string getWeather(const std::string& cityName) {
		std::string jsonResponse;

		if (curl) {
			std::string url = "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&appid=" + apiKey;

			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK) {
				std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
			}
		}

		return jsonResponse;
	}
};