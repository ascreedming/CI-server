#include "gtest/gtest.h"
#include "integrationTest.hpp"

/*
*   This test will determine if the checkout part of integration test works as intended
*   The function should be able to determine if the checkout was done correcly and report
*   that. It should also know if something went wrong and report that aswell.
*/


// report merge(std::string sourceFolder, std::string cacheFolder, std::string targetBranch)
TEST(merge, correctly)
{
    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";
    std::string cacheFolder = "./temp/cache";

    // Create folders
    std::string cmd = "mkdir -p " + buildFolder + " " + sourceFolder + " " + cacheFolder;
    std::string cmd_output = exec(cmd.c_str());


    std::string repo = "git@github.com:Pihlqvist/ci_test.git";
    std::string commit = "6cc7e58d7cb0e4b7c06eee65f1f49b336050db22";
    std::string targetBranch = "origin/assurance";

    // Assuming in this test that cloning works correcly, should be changed to a 
    // mock test in future
    cloning(sourceFolder, cacheFolder, repo);
    checkout(sourceFolder, cacheFolder, commit);

    report r = merge(sourceFolder, targetBranch);
    

    EXPECT_STREQ("Merge went fine.", r.message.c_str());
    EXPECT_EQ(0, r.errorcode);

    // Cleanup
    system("rm -rf ./temp");
}


/*
// report checkout(std::string sourceFolder, std::string commit)
TEST(checkout, fatal)
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