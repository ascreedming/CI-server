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
void cloning(std::string sourceFolder, std::string repo)
{
    std::string cmd = "git clone " + repo + " " + sourceFolder;
    std::string cmd_output = exec(cmd.c_str());

    if (cmd_output.find("done.") != std::string::npos)
    {
        std::cout << "Cloning done!\n";
    }
    else if (cmd_output.find("fatal:") != std::string::npos)
    {
        std::cout << "Fatal\n";
    }
    else
    {
        std::cerr << "Unknown Error in cloning\n";
    }

}

// Checkout the given 'commit'
void checkout(std::string sourceFolder, std::string commit)
{
    std::string cmd = "git --git-dir " + sourceFolder + "/.git checkout " + commit;
    std::string cmd_output = exec(cmd.c_str());


    if (cmd_output.find("HEAD is now at") != std::string::npos)
    {
        std::cout << "We could set HEAD to commit\n";
    }
    else
    {
        std::cerr << "Unknown Error in git checkout\n";
    }
}


// Merge to the target branch and determine if it could be done
void merge(std::string sourceFolder, std::string targetBranch)
{
    std::string cmd = "git --git-dir " + sourceFolder + "/.git merge " + targetBranch;
    std::string cmd_output = exec(cmd.c_str());


    if (cmd_output.find("Already up to date.") != std::string::npos)
    {
        std::cout << "Merge went fine\n";
    }
    else
    {
        std::cerr << "Unkown error in merge\n";
    }
}

// Determine if CMake could compile the code
void compileCMake(std::string sourceFolder, std::string buildFolder)
{
    // Create build folder
    std::string cmd = "mkdir " + buildFolder;
    std::string cmd_output = exec(cmd.c_str());

    // Performe cmake
    cmd = "cmake -B" + buildFolder + " -H" + sourceFolder;
    cmd_output = exec(cmd.c_str());

    //std::cerr << cmd_output; // USED IN DEBUGGING

    if (cmd_output.find("Generating done") != std::string::npos)
    {
        std::cout << "CMake compiled fine\n";
    }
    else 
    {
        std::cerr << "CMake din't compile\n";
    }

}

// Compile with the make file cretade by CMake in prev step
void compileMake(std::string buildFolder)
{
    std::string cmd = "make -C " + buildFolder;
    std::string cmd_output = exec(cmd.c_str());    


    if (cmd_output.find("100%") != std::string::npos)
    {
        std::cout << "Make compiled fine\n";
    }
    else 
    {
        std::cerr << "Make din't compile\n";
    }
}

// Run unittests in build folder
void runUnittest(std::string buildFolder)
{
    std::string cmd = buildFolder + "/unittest"; 
    std::string cmd_output = exec(cmd.c_str());


    if (cmd_output.find("PASSED") != std::string::npos)
    {
        std::cout << "Passed all unittests\n";
    }
    else 
    {
        std::cerr << "Failed unittests\n";
    }
}

void integrationTest()
{
    // Should be in the input
    std::string commit = "486caa7143d20d47a0afb5dbd3b044bca28ab30d";
    std::string repo = "git@github.com:Naxaes/CI-server.git";
    std::string targetBranch = "master";

    // Folders creatade during testing
    std::string buildFolder = "../temp/build";
    std::string sourceFolder = "../temp/src";

    // Clone the repo into 'sourceFolder'
    cloning(sourceFolder, repo);

    // Checkout the given 'commit'
    checkout(sourceFolder, commit);

    // Performe a merge into 'targetBranch' to see if it can be done without issue
    merge(sourceFolder, targetBranch);
    
    // Compile the code with 'CMake'
    compileCMake(sourceFolder, buildFolder);

    // Comple the code with 'make'
    compileMake(buildFolder);

    // Performe unittest
    runUnittest(buildFolder);

    // Cleanup
    exec("rm -rf ../temp");


    // Report results
}

int main()
{
    integrationTest();

    return 0;
}