#ifndef INCLUDE_INTEGRATION_TEST_
#define INCLUDE_INTEGRATION_TEST_

#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


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
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


// Clone the current repo into a selected folder
report cloning(std::string sourceFolder, std::string repo)
{
    std::string cmd = "git clone " + repo + " " + sourceFolder;
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("done.") != std::string::npos)
    {
        rep.message = "Cloning done.";
        rep.errorcode = 0;
    }
    else if (cmd_output.find("fatal:") != std::string::npos)
    {
        rep.message = "Fatal\n";
        rep.errorcode = 2;
    }
    else
    {
        rep.message = "Unknown Error in cloning";
        rep.errorcode = 1;
    }

    return rep;
}

// Checkout the given 'commit'
report checkout(std::string sourceFolder, std::string commit)
{
    std::string cmd = "git --git-dir " + sourceFolder + "/.git checkout " + commit;
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("HEAD is now at") != std::string::npos)
    {
        rep.message = "We could set HEAD to commit";
        rep.errorcode = 1;
    }
    else
    {
        std::cerr << "Unknown Error in git checkout";
    }

    return rep;
}


// Merge to the target branch and determine if it could be done
report merge(std::string sourceFolder, std::string targetBranch)
{
    std::string cmd = "git --git-dir " + sourceFolder + "/.git merge " + targetBranch;
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("Already up to date.") != std::string::npos)
    {
        rep.message = "Merge went fine";
        rep.errorcode = 0;
    }
    else
    {
        rep.message = "Unkown error in merge";
        rep.errorcode = 1;
    }

    return rep;
}

// Determine if CMake could compile the code
report compileCMake(std::string sourceFolder, std::string buildFolder)
{
    // Create build folder
    std::string cmd = "mkdir " + buildFolder;
    std::string cmd_output = exec(cmd.c_str());

    // Performe cmake
    cmd = "cmake -B" + buildFolder + " -H" + sourceFolder;
    cmd_output = exec(cmd.c_str());

    //std::cerr << cmd_output; // USED IN DEBUGGING
    report rep;
    if (cmd_output.find("Generating done") != std::string::npos)
    {
        rep.message = "CMake compiled fine";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "CMake din't compile";
        rep.errorcode = 0;
    }

    return rep;
}

// Compile with the make file cretade by CMake in prev step
report compileMake(std::string buildFolder)
{
    std::string cmd = "make -C " + buildFolder;
    std::string cmd_output = exec(cmd.c_str());    

    report rep;
    if (cmd_output.find("100%") != std::string::npos)
    {
        rep.message = "Make compiled fine";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "Make din't compile";
        rep.errorcode = 1;
    }

    return rep;
}

// Run unittests in build folder
report runUnittest(std::string buildFolder)
{
    std::string cmd = buildFolder + "/unittest"; 
    std::string cmd_output = exec(cmd.c_str());

    report rep;
    if (cmd_output.find("PASSED") != std::string::npos)
    {
        rep.message = "Passed all unittests";
        rep.errorcode = 0;
    }
    else 
    {
        rep.message = "Failed unittests";
        rep.errorcode = 1;
    }
    
    return rep;
}

report integrationTest()
{
    // Should be in the input
    std::string commit = "486caa7143d20d47a0afb5dbd3b044bca28ab30d";
    std::string repo = "git@github.com:Naxaes/CI-server.git";
    std::string targetBranch = "master";

    // Folders creatade during testing
    std::string buildFolder = "./temp/build";
    std::string sourceFolder = "./temp/src";

    std::array<report, 6> reports;

    // Clone the repo into 'sourceFolder'
    reports[0] = cloning(sourceFolder, repo);
    if (reports[0].errorcode != 0)
    {
        // something is not correct
        return reports[0];
    }

    // Checkout the given 'commit'
    checkout(sourceFolder, commit);
    if (reports[1].errorcode != 0)
    {
        // something is not correct
        return reports[1];
    }

    // Performe a merge into 'targetBranch' to see if it can be done without issue
    merge(sourceFolder, targetBranch);
    if (reports[2].errorcode != 0)
    {
        // something is not correct
        return reports[2];
    }    

    // Compile the code with 'CMake'
    compileCMake(sourceFolder, buildFolder);
    if (reports[3].errorcode != 0)
    {
        // something is not correct
        return reports[3];
    }

    // Comple the code with 'make'
    compileMake(buildFolder);
    if (reports[4].errorcode != 0)
    {
        // something is not correct
        return reports[4];
    }

    // Performe unittest
    runUnittest(buildFolder);
    if (reports[5].errorcode != 0)
    {
        // something is not correct
        return reports[5];
    }

    // Cleanup
    exec("rm -rf ./temp");


    // Report results
    return {0, "Everthing is good"};
}


#endif  // INCLUDE_INTEGRATION_TEST_