#include "gtest/gtest.h"
#include "integrationTest.hpp"

/*
*   This test will determine if the cloning part of integration test works as intended
*   The function should be able to determine if the cloning was done correcly and report
*   that. It should also know if something went wrong and report that aswell.
*/


// report cloning(std::string sourceFolder, std::string repo)
TEST(cloning, correctly)
{
    std::string sourceFolder = "./temp";
    std::string repo = "git@github.com:Naxaes/CI-server.git";

    report r = cloning(sourceFolder, repo);

    EXPECT_STREQ("Cloning done.", r.message.c_str());
    EXPECT_EQ(0, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}