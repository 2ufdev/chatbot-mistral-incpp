#include <iostream>
#include <string>
#include <windows.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fcntl.h>
#include <io.h>

using json = nlohmann::json;

std::string wstring_to_utf8(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &strTo[0], size_needed, nullptr, nullptr);
    return strTo;
}

std::wstring utf8_to_wstring(const std::string& str) {
    if (str.empty()) return {};
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), nullptr, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    std::wstring user_input;
    std::string api_key = "OgH0dTv5ZqfThyHQ3R5z6QbwkFrqncJ7";

    std::wcout << L"chatbot\nenter 'exit' to leave\n";

    while (true) {
        std::wcout << L"\n> ";
        std::getline(std::wcin, user_input);
        if (user_input == L"exit") break;

        std::string input = wstring_to_utf8(user_input);
        CURL* curl = curl_easy_init();
        if (!curl) return 1;

        std::string response_buffer;
        curl_easy_setopt(curl, CURLOPT_URL, "https://codestral.mistral.ai/v1/chat/completions");

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        json payload = {
            {"model", "codestral-latest"},
            {"messages", json::array({{{"role", "user"}, {"content", input}}})}
        };

        std::string json_payload = payload.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

        CURLcode curl_result = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (curl_result != CURLE_OK) {
            std::wcout << L"curl err: " << curl_easy_strerror(curl_result) << L"\n";
            continue;
        }

        auto response = json::parse(response_buffer, nullptr, false);
        if (response.contains("choices")) {
            std::wstring reply = utf8_to_wstring(response["choices"][0]["message"]["content"].get<std::string>());
            std::wcout << L"bot: " << reply << L"\n";
        }
        else {
            std::wcout << L"err inv reps\n";
        }
    }

    return 0;
}
