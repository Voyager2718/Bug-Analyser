#ifndef GENERAL_BUG_ANALYSER_H
#define GENERAL_BUG_ANALYSER_H

#include<string>
#include<memory>
#include<vector>
#include"BugAnalyser.Interface.h"

using std::string;
using std::shared_ptr;
using std::vector;

class GeneralBugAnalyser : BugAnalyserInterface{
public:
    GeneralBugAnalyser(string bug_log_location);

    GeneralBugAnalyser();

    static shared_ptr< BugAnalyserInterface > analyse(vector< string > lines_of_log);
};

#endif