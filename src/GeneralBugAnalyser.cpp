#include<memory>
#include<string>
#include<memory>
#include<vector>

#include"Report.h"
#include"GeneralBugAnalyser.h"

using std::string;
using std::shared_ptr;
using std::vector;

GeneralBugAnalyser::GeneralBugAnalyser(string bug_log_location){

}

GeneralBugAnalyser::GeneralBugAnalyser(){

}

shared_ptr< BugAnalyserInterface > GeneralBugAnalyser::analyse(vector< string > lines_of_log) {
    //TODO: Analyse some lines, if this class can handle, return this class's instance. If not, return null.
    return nullptr;
}

shared_ptr<Report> GeneralBugAnalyser::analyseLog(string bug_log_location) {
    shared_ptr<Report> report(new Report());
    //TODO
    return report;
}