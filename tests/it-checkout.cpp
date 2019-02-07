#include "gtest/gtest.h"
#include "integrationTest.hpp"

/*
*   This test will determine if the checkout part of integration test works as intended
*   The function should be able to determine if the checkout was done correcly and report
*   that. It should also know if something went wrong and report that aswell.
*/


// report checkout(std::string sourceFolder, std::string commit)
TEST(cloning, correctly)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());


    std::string repo = "git@github.com:Pihlqvist/ci_test.git";
    std::string commit = "c78f6147592663bdf057d0382ca883df3eff7082";

    // Assuming in this test that cloning works correcly, should be changed to a 
    // mock test in future
    cloning(sourceFolder, cacheFolder, repo);

    report r = checkout(sourceFolder, commit);
    

    EXPECT_STREQ("We could set HEAD to commit.", r.message.c_str());
    EXPECT_EQ(0, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}


/*
// report checkout(std::string sourceFolder, std::string commit)
TEST(cloning, fatal)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());


    std::string repo = "git@github.com:Pihlqvist/ci_test_WRONG.git";

    report r = cloning(sourceFolder, cacheFolder, repo);

    EXPECT_STREQ("Fatal error while cloning.", r.message.c_str());
    EXPECT_EQ(2, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}
*/