#ifndef GENERAL_BUG_ANALYSER_H
#define GENERAL_BUG_ANALYSER_H

#include<string>
#include"BugAnalyser.Interface.h"

using std::string;

class GeneralBugAnalyser : BugAnalyserInterface{
public:
    GeneralBugAnalyser(string bug_log_location){
        
    }
    GeneralBugAnalyser(){
        
    }

    virtual shared_ptr<Report> analyse(string bug_log_location){
        shared_ptr<Report> report(new Report);
        return report;
    }
};

#endif