//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_COOPFUNC_H
#define SEARCHENGINE_COOPFUNC_H
#pragma once
#include <filesystem>

std::vector<std::string> splitString(const std::string &str, const std::string &del);

void generateRequest(std::filesystem::path exeDir, std::vector<std::string> *allWords);

void generateFiles(std::vector<std::string> files, std::filesystem::path exeDir);

std::filesystem::path strToDir(const std::string &strDir);

std::string strToLow(const std::string &input);

std::string delPunctuation(const std::string &str);

#endif //SEARCHENGINE_COOPFUNC_H
