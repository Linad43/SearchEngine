//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_DOCUMENT_H
#define SEARCHENGINE_DOCUMENT_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "nlohmann/json.hpp"


class Document {
public:
    inline static int nextId = 0;
    int docid;
    std::filesystem::path filepath;
    std::string text;

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
        text = "";
        std::cout << "Loading file " << filepath << std::endl;
        while (file >> buf) {
            text += buf + " ";
        }
        nlohmann::json j;
        j["docid"] = docid;
        j["filepath"] = filepath;
        j["text"] = text;
        std::cout << j.dump(4) << std::endl;
        file.close();
    }
};

#endif //SEARCHENGINE_DOCUMENT_H
