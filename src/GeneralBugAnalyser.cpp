#include<memory>

#include"BugAnalyser.Interface.h"
#include"Report.h"

using std::shared_ptr;

class GeneralBugAnalyser:BugAnalyserInterface{
public:
    virtual shared_ptr<Report> analyse(string bug) override {
        shared_ptr<Report> report(new Report());
        //TODO
        return report;
    }
};