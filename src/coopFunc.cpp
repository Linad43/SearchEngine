//
// Created by linad on 05.03.2026.
//
#include <string>
#include <vector>
#include "coopFunc.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

std::vector<std::string> splitString(const std::string &str, const std::string &del) {
    std::string str_in = str;
    std::vector<std::string> result;

    while (true) {
        const auto pos = str_in.find(del);
        result.push_back(str_in.substr(0, pos));
        str_in = str_in.substr(pos + 1);
        if (pos == std::string::npos) {
            break;
        }
    }
    return result;
}

void generateRequest(std::filesystem::path exeDir, std::vector<std::string> *allWords) {
    std::vector<std::string> requests;
    auto requestDir = exeDir / "request.json";
    std::ofstream file(requestDir);
    if (!file.is_open()) {
        std::cerr << "Not found file " << requestDir << std::endl;
        return;
    }

    std::string buf = "";
    for (auto i = 0; i < (rand() % 999) + 1; i++) {
        for (auto j = 0; j < (rand() % 9) + 1; j++) {
            if (j != 0) {
                buf += " ";
            }
            buf += allWords->at(rand() % allWords->size());
        }
        requests.push_back(buf);
        buf = "";
    }

    nlohmann::json json;
    json["requests"] = requests;
    file << json.dump(4);
}

/**
 *
 * @param files list files for searched
 * @param exeDir direct .exe file
 *
 *
 *
 */
void generateFiles(std::vector<std::string> files, std::filesystem::path exeDir) {
    std::cout << "Generating files" << std::endl;
    auto bufDir = exeDir; // for direct created files
    std::vector<std::string> allWords; // words for full file
    // get words from file
    if (std::fstream fileWords(exeDir / "words_alpha.txt"); fileWords.is_open()) {
        std::string buf;
        while (std::getline(fileWords, buf)) {
            allWords.push_back(buf.erase(buf.size() - 1));
        }
    } else {
        return;
    }

    // created direct files
    for (auto i = 0; i < files.size(); i++) {
        auto filePath = splitString(files[i], "/");
        for (auto j = 0; j < filePath.size(); j++) {
            if (filePath[j] != "." && filePath[j] != ".." && j != filePath.size() - 1) {
                bufDir = bufDir / filePath[j];
                std::filesystem::create_directory(bufDir);
            } else if (j == filePath.size() - 1) {
                bufDir = bufDir / filePath[j];
            }
        }
        // created files and full file
        std::ofstream file(bufDir);
        if (file.is_open()) {
            for (int j = 0; j < rand() % 1000; j++) {
                file << allWords[rand() % allWords.size()] << " ";
            }
        }
        bufDir = exeDir;
    }
    generateRequest(exeDir, &allWords);
}

std::filesystem::path strToDir(const std::string &strDir) {
    std::filesystem::path result;
    auto filePath = splitString(strDir, "/");
    for (auto j = 0; j < filePath.size(); j++) {
        if (filePath[j] != "." && filePath[j] != "..") {
            result = result / filePath[j];
        }
    }
    return result;
}

std::string strToLow(const std::string &input) {
    std::string result = input;
    for (char &i: result) {
        i = tolower(i);
    }
    return result;
}

std::string delPunctuation(const std::string &str) {
    std::string result = "";
    for (const char i : str) {
        if (i != '.'
            && i != ','
            && i != '_'
            && i != ';'
            && i != ':') {
            result += i;
        }
    }
    return result;
}
