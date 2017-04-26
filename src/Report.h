#ifndef REPORT_H
#define REPORT_H

#include<memory>
#include<string>
#include<vector>
#include<map>

using std::string;
using std::map;
using std::vector;

class Report{
private:
    vector< map < string, string> >reports;
public:
    virtual void add_report(map <string, string >);
    virtual vector< map < string, string> > get_reports();
    virtual map < string, string > get_report(int);
    virtual Report operator+(const Report& report);
};

#endif