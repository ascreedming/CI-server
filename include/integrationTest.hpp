#ifndef INCLUDE_INTEGRATIONTEST_H_
#define INCLUDE_INTEGRATIONTEST_H_

#include <string>

/*
*   This file is indentent to hold the function that conducts the test of the commit
*
*
*/

struct report
{
    int errorcode;          // 0 -> good, 1 > -> bad
    std::string message;    // message for more info
};

// Performes a system call and returns the output as a string
std::string exec(const char* cmd);

// Clone the current repo into a selected folder
report cloning(std::string sourceFolder, std::string cacheFolder, std::string repo);

// Checkout the given 'commit'
report checkout(std::string sourceFolder, std::string cacheFolder, std::string commit);

// Merge to the target branch and determine if it could be done
report merge(std::string sourceFolder, std::string targetBranch);

// Determine if CMake could compile the code
report compileCMake(std::string sourceFolder, std::string buildFolder);

// Compile with the make file cretade by CMake in prev step
report compileMake(std::string buildFolder);

// Run unittests in build folder
report runUnittest(std::string buildFolder);

//
report integrationTest(std::string commit, std::string repo, std::string targetBranch);


#endif  // INCLUDE_INTEGRATIONTEST_H_