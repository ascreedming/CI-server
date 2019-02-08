#include "gtest/gtest.h"
#include "integrationTest.hpp"

/*
*   Unittest for integrationTest function. This will do all the steps 
*   in the check and determine if it's okay
*/


//report integrationTest(std::string commit, std::string repo, std::string targetBranch)
TEST(runUnittest, correctly)
{

    std::string repo = "git@github.com:Pihlqvist/ci_test.git";
    std::string commit = "6cc7e58d7cb0e4b7c06eee65f1f49b336050db22";
    std::string targetBranch = "origin/assurance";

    report r = integrationTest(commit, repo, targetBranch);

    EXPECT_STREQ("Everthing is good.", r.message.c_str());
    EXPECT_EQ(0, r.errorcode);

}
