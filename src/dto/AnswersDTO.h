//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_ANSWERSDTO_H
#define SEARCHENGINE_ANSWERSDTO_H


#pragma once
#include <map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class RelevanceItem {
public:
    int docid;
    double rank;

    RelevanceItem(
        const int docid,
        const double rank)
        : docid(docid),
          rank(rank) {
    }

    nlohmann::json toJson() {
        nlohmann::json j;
        j["docid"] = docid;
        j["rank"] = rank;
        return j;
    }

    std::string toString() {
        return toJson().dump(4);
    }
};

class RequestAnswer {
public:
    bool result;
    std::vector<RelevanceItem> relevance;

    RequestAnswer() = default;

    RequestAnswer(
        const bool result,
        const std::vector<RelevanceItem> &relevance)
        : result(result),
          relevance(relevance) {
    }

    nlohmann::json toJson() {
        nlohmann::json j;
        j["result"] = result;
        j["relevance"] = nlohmann::json::object();
        for (auto &relevanceItem: relevance) {
            j["answers"] = relevanceItem.toJson();
        }
        return j;
    }

    std::string toString() {
        return toJson().dump(4);
    }
};

class AnswersDTO {
public:
    std::map<std::string, RequestAnswer> answers;

    AnswersDTO(
        const std::map<std::string, RequestAnswer> &answers)
        : answers(answers) {
    }

    nlohmann::json toJson() {
        nlohmann::json j;
        j["answers"] = nlohmann::json::object();
        for (auto &[key, value]: answers) {
            j["answers"][key] = value.toJson();
        }
        return j;
    }

    std::string toString() {
        return toJson().dump(4);
    }
};

#endif //SEARCHENGINE_ANSWERSDTO_H
