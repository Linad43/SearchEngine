//
// Created by linad on 05.03.2026.
//

#include <gtest/gtest.h>
#include "../src/dto/ConfigDTO.h"
#include "../src/dto/Document.h"
// #include "../src/coopFunc.h"
#include "../src/coopFunc.cpp"
#include <iostream>

#include "../src/dto/Document.h"

// TEST(DummyTest, BasicAssertion) {
//     Config cfg(strToDir("tests/resources/config_test.json"));
//     EXPECT_EQ(cfg.name, "TestEngine");
//     std::cout << cfg.toString() << std::endl;
// }
TEST(ConfigTest, LoadAndSerialize) {
    // const auto exeDir = std::filesystem::current_path();
    std::string direct = "config_test.json";
    std::filesystem::path dir = strToDir(direct);
    Config cfg(dir);

    EXPECT_EQ(cfg.name, "TestEngine");
    EXPECT_EQ(cfg.version, "0.0.1");
    EXPECT_EQ(cfg.max_responses, 3);
    ASSERT_EQ(cfg.files.size(), 2);
    EXPECT_EQ(cfg.files[0], "file1.txt");

    auto j = cfg.toJson();
    EXPECT_EQ(j["config"]["name"], "TestEngine");
    EXPECT_EQ(j["files"].size(), 2);
    std::cout << cfg.toString() << std::endl;

    std::cout << "JSON output:\n" << cfg.toJson().dump(4) << std::endl;

    for (int i = 0; i < cfg.files.size(); i++) {
        new Document(strToDir(cfg.files[i]));
    }
}
