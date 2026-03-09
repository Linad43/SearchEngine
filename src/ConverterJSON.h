//
// Created by linad on 09.03.2026.
//

#ifndef SEARCHENGINE_CONVERTERJSON_H
#define SEARCHENGINE_CONVERTERJSON_H
#include <string>
#include <vector>

#include "SearchEngine.h"
#include "dto/RequestDTO.h"

class ConverterJSON {
public:
    ConverterJSON() = default;

    RequestsDTO getResponses() {
        RequestsDTO requests = RequestsDTO("requests.json");
        return requests;
    }

    void putAnswers(std::vector<std::vector<std::pair<int, float> > > answers) {
        auto resultAnswers = AnswersDTO();

        for (auto i = 0; i < answers.size(); ++i) {
            RequestAnswer requestAnswer;

            if (answers[i].empty()) {
                requestAnswer.result = false;
            } else {
                requestAnswer.result = true;
                for (auto &answerItem: answers[i]) {
                    auto item = RelevanceItem(answerItem.first, answerItem.second);
                    requestAnswer.relevance.emplace_back(item);
                }
            }

            auto key = std::to_string(i + 1);
            while (key.size() < 3) {
                key = "0" + key;
            }
            key = "request" + key;
            resultAnswers.answers[key] = requestAnswer;
        }
        if (std::ofstream file("answers.json"); file.is_open()) {
            file << resultAnswers.toString();
        }
    }
};


#endif //SEARCHENGINE_CONVERTERJSON_H
