add_executable(SearchEngineTests
        test_search.cpp
)

target_link_libraries(SearchEngineTests
        PRIVATE
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(SearchEngineTests)