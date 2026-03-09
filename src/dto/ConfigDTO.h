//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_CONFIGDTO_H
#define SEARCHENGINE_CONFIGDTO_H

#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#define CURRENT_VERSION "1.0.0"

class Config {
public:
    std::string name;
    std::string version;
    int max_responses;
    std::vector<std::string> files;

    // Конструктор из файла
    Config(const std::filesystem::path &directConfig) {
        std::ifstream file(directConfig);
        std::cout << std::filesystem::absolute(directConfig) << std::endl;

        //config file is missing
        if (!file.is_open())
            throw std::runtime_error("Cannot open config file: " + std::filesystem::absolute(directConfig).string());

        //config file is empty
        if (file.peek() == std::ifstream::traits_type::eof())
            throw std::runtime_error("Config file is empty!");

        nlohmann::json j;
        file >> j;

        auto cfg = j.at("config");
        name = cfg.at("name").get<std::string>();
        version = cfg.at("version").get<std::string>();
        max_responses = cfg.at("max_responses").get<int>();

        //config.json has incorrect file version
        if (version != CURRENT_VERSION)
            throw std::runtime_error("Config file version mismatch."
                                     "\nCurrent version " CURRENT_VERSION ", version configs " + version);

        files = j.at("files").get<std::vector<std::string> >();
    }

    // Метод сериализации обратно в JSON
    nlohmann::json toJson() const {
        nlohmann::json j;
        j["config"]["name"] = name;
        j["config"]["version"] = version;
        j["config"]["max_responses"] = max_responses;
        j["files"] = files;
        return j;
    }


    std::string toString() const {
        return toJson().dump(4);
    }
};

#endif //SEARCHENGINE_CONFIGDTO_H
