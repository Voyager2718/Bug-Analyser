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

void Report::add_reports(vector< map< string, string > > report) {
    this->reports.insert(this->reports.end(), reports.begin(), reports.end());
}

vector< map < string, string> > Report::get_reports() const {
    return reports;
}

map < string, string > Report::get_report(int index) const {
    return reports[index];
}

Report Report::operator+(const Report& report){
    Report temp;
    temp.add_reports(this->reports);
    temp.add_reports(report.get_reports());
    return report;
}

void Report::merge_reports(Report reports){
    vector< map < string, string> >temp = reports.get_reports();
    this->reports.insert(this->reports.end(), temp.begin(), temp.end());
}