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
    vector< map < string, string> >reports; //If have used stack elements, must overload copy constructor and operator=. Because Report have operator+, otherwise, elements may not be copied completely.
public:
    virtual void add_report(map <string, string >);
    virtual void add_reports(vector< map <string, string > >);
    virtual vector< map < string, string> > get_reports() const;
    virtual map < string, string > get_report(int) const;
    virtual Report operator+(const Report&);
    virtual void merge_reports(Report);
};

#endif