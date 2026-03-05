//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_REQUESTDTO_H
#define SEARCHENGINE_REQUESTDTO_H


#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class RequestsDTO {
public:
    std::vector<std::string> requests;

    RequestsDTO(const std::filesystem::path &directRequest) {
        std::ifstream file(directRequest);
        if (!file.is_open())
            throw std::runtime_error("Cannot open config file: " + directRequest.string());

        nlohmann::json j;
        file >> j;

        requests = j.at("requests").get<std::vector<std::string> >();
    }

    nlohmann::json toJson() {
        nlohmann::json j;
        j["requests"] = requests;
        return j;
    }

    std::string toString() {
        return toJson().dump(4);
    }
};

#endif //SEARCHENGINE_REQUESTDTO_H
