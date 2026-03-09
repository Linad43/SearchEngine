//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_SEARCHENGINE_H
#define SEARCHENGINE_SEARCHENGINE_H
#include "coopFunc.h"
#include <vector>
#include <ranges>
#include <algorithm>
#include "dto/AnswersDTO.h"
#include "dto/ConfigDTO.h"
#include "dto/Document.h"
#include "dto/Indexer.h"
#include <future>

class SearchEngine {
    Config *cfg;
    Indexer *idx;

public:
    SearchEngine() {
        cfg = new Config(strToDir("config_test.json"));
        std::vector<Document> docs;

        for (const auto &dir: cfg->files) {
            // std::cout << dir << std::endl;
            docs.emplace_back(dir);
        }
        idx = new Indexer();
        for (auto &doc: docs) {
            // std::cout << doc.toString() << std::endl;
            idx->addDocument(doc);
        }
        // std::cout << idx->toString() << std::endl;
    }

    std::vector<std::pair<int, float> > search(std::string query) {
        std::map<int, float> relevance;
        auto bufQuery = splitString(query, " ");
        int maxScore = 0;
        for (auto word: bufQuery) {
            if (idx->index.contains(word)) {
                for (auto it = idx->index[word].begin(); it != idx->index[word].end(); ++it) {
                    relevance[it->first] += it->second;
                    if (maxScore < relevance[it->first]) {
                        maxScore = relevance[it->first];
                    }
                }
            }
        }

        for (auto it = relevance.begin(); it != relevance.end(); ++it) {
            if (maxScore != 0)
                it->second /= maxScore;
            else
                it->second = 0;
        }

        std::vector<std::pair<int, float> > results;
        for (auto pair: relevance) {
            results.emplace_back(pair.first, pair.second);
        }
        std::ranges::sort(results, [](const auto &a, const auto &b) {
            return a.second > b.second;
        });

        if (results.size() > cfg->max_responses) {
            results.resize(cfg->max_responses);
        }

        return results;
    }
    std::vector<std::vector<std::pair<int, float> > > searchAllRequests(std::vector<std::string > requests) {

        std::vector<std::future<std::vector<std::pair<int, float>>>> futures;

        // запускаем потоки
        for (const auto& request : requests) {
            futures.push_back(
                std::async(std::launch::async, [this, request]() {
                    return search(request);
                })
            );
        }

        // собираем результаты
        std::vector<std::vector<std::pair<int, float>>> results;

        for (auto& f : futures) {
            results.push_back(f.get());
        }

        return results;
    }
};


#endif //SEARCHENGINE_SEARCHENGINE_H
