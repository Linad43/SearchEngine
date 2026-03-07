//
// Created by linad on 05.03.2026.
//

#ifndef SEARCHENGINE_SEARCHENGINE_H
#define SEARCHENGINE_SEARCHENGINE_H
#include "coopFunc.h"
#include "dto/AnswersDTO.h"
#include "dto/ConfigDTO.h"
#include "dto/Document.h"
#include "dto/Indexer.h"


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


    std::map<int, float>::iterator findMaxRelevance(std::map<int, float> *relevance) {
        auto maxRelevance = relevance->begin();

        for (auto it = relevance->begin(); it != relevance->end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }

        for (auto it = relevance->begin(); it != relevance->end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
            if (maxRelevance->second < it->second) {
                maxRelevance = it;
            }
        }
        relevance->erase(maxRelevance);

        for (auto it = relevance->begin(); it != relevance->end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }

        return maxRelevance;
    }

    /*std::vector<std::vector<std::pair<int, float> > >*/
    std::vector<std::vector<std::pair<int, float> > > search(std::vector<std::string> query) {
        std::map<int, float> relevance;
        int maxScore = 0;
        for (auto word: query) {
            for (auto it = idx->index[word].begin(); it != idx->index[word].end(); ++it) {
                relevance[it->first] += it->second;
                if (maxScore < relevance[it->first]) {
                    maxScore = relevance[it->first];
                }
            }
        }

        for (auto it = relevance.begin(); it != relevance.end(); ++it) {
            it->second /= maxScore;
        }

        std::vector<std::vector<std::pair<int, float> > > results;

        int const size = (relevance.size() - 1) < cfg->max_responses ? (relevance.size()-1) : cfg->max_responses;
        std::vector<std::pair<int, float> > bufResult;
        for (int i = 0; i <= size; ++i) {
            auto bufMax = relevance.end();

            for (auto it = relevance.begin(); it != relevance.end(); ++it) {
                if (bufMax->second < it->second && !findInVector(&bufResult, *it)) {
                    bufMax = it;
                }
            }
            bufResult.emplace_back(bufMax->first, bufMax->second);
        }
        nlohmann::json j = bufResult;
        std::cout << j.dump(4) << std::endl;
        results.push_back(bufResult);
        return results;
    }

    static bool findInVector(const std::vector<std::pair<int, float> > *vec, const std::pair<int, float> &item) {
        for (const auto & it : *vec) {
            if (it.first == item.first) {
                return true;
            }
        }
        return false;
    }
};


#endif //SEARCHENGINE_SEARCHENGINE_H
