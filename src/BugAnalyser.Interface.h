#ifndef BUG_ANALYSER_INTERFACE_H
#define BUG_ANALYSER_INTERFACE_H

#include<string>
#include<memory>

#include"Report.h"

using std::string;
using std::shared_ptr;

class BugAnalyserInterface{
public:
    virtual shared_ptr<Report> analyse(string bug_log_location) = 0;
};

#endif