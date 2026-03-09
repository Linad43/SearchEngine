//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_DOCUMENT_H
#define SEARCHENGINE_DOCUMENT_H
#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "../coopFunc.h"
#include "nlohmann/json.hpp"


class Document {
public:
    inline static int nextId = 0;
    int docid;
    std::filesystem::path filepath;
    std::map<std::string, int> text;

    Document(
        const std::filesystem::path &filepath) {
        this->docid = nextId++;
        this->filepath = filepath;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cout << "Failed to open file " << filepath << std::endl;
            return;
        }
        std::string buf;
        // std::cout << "Loading file " << filepath << std::endl;
        while (file >> buf) {
            buf = strToLow(delPunctuation(buf));
            if (text.contains(buf)) {
                text[buf]++;
            } else {
                text[buf] = 1;
            }
        }
        // std::cout << toString() << std::endl;
        file.close();
    }
    nlohmann::json toJson() {
        nlohmann::json j;
        j["docid"] = docid;
        j["filepath"] = filepath;
        j["text"] = text;
        return j;
    }
    std::string toString() {
        return toJson().dump(4);
    }

};

#endif //SEARCHENGINE_DOCUMENT_H
