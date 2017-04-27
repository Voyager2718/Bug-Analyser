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
    analyser_name = "General Bug Analyser";
    _bug_log_location = bug_log_location;
}

GeneralBugAnalyser::GeneralBugAnalyser(){
    analyser_name = "General Bug Analyser";
}

shared_ptr< BugAnalyserAbstract > GeneralBugAnalyser::analyse(vector< string > lines_of_log) {
    //TODO: Analyse some lines, if this class can handle, return this class's instance. If not, return null.
    //TODO: BTW, if this class can handle, new an object with the log that interests this class. Or the app will crash.
    return nullptr;
}