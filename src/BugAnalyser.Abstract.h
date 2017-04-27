#ifndef BUG_ANALYSER_INTERFACE_H
#define BUG_ANALYSER_INTERFACE_H

#include<string>
#include<memory>
#include<vector>

#include"Report.h"

using std::string;
using std::shared_ptr;

class BugAnalyserAbstract{
protected:
    string analyser_name;
    string _bug_log_location;
    vector< shared_ptr< BugAnalyserAbstract >(*)( vector< string > ) > analysts;
    BugAnalyserAbstract();
public:
    virtual BugAnalyserAbstract& add_analyst(shared_ptr< BugAnalyserAbstract >(*)( vector< string > ));

    virtual BugAnalyserAbstract& add_analyst(vector< shared_ptr< BugAnalyserAbstract >(*)( vector< string > ) >);

    static shared_ptr< BugAnalyserAbstract > analyse(vector< string > lines_of_log);

    virtual shared_ptr< Report > analyse_log(string bug_log_location);

    virtual shared_ptr< Report > analyse_log();
};

#endif