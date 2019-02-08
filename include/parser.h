#include "json.hpp"

#ifndef WEBHOOK_PARSER_H
#define WEBHOOK_PARSER_H

//#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Parser {

    json test;
    json message;

public:
    Parser();

    Parser(string json_message);

    string get_action();

    string get_pr_url();

    string get_clone_url();

    string get_pr_title();

    string get_pr_body();

    string get_pr_time();

    string get_pr_user();
};

#endif //WEBHOOK_PARSER_H
