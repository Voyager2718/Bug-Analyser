#include"BugAnalyser.Interface.h"

BugAnalyserInterface& BugAnalyserInterface::add_analyst(shared_ptr< BugAnalyserInterface >(*analyst)( vector< string > )){
    analysts.push_back(analyst);
    return *this;
}


shared_ptr<Report> BugAnalyserInterface::analyseLog(string bug_log_location) {
    shared_ptr<Report> report(new Report());
    //TODO: Analyse an entire .log or .trc file.
    return report;
}