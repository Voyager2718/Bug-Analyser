#include<memory>
#include<string>
#include<vector>
#include<map>

#include"Report.h"

using std::string;
using std::map;
using std::vector;

void Report::add_report(map< string, string > report){
    reports.push_back(report);
}

vector< map < string, string> > Report::get_reports(){
    return reports;
}

map < string, string > Report::get_report(int index){
    return reports[index];
}

Report Report::operator+(const Report& report){
    return report;//TODO: Concat 2 reports
}