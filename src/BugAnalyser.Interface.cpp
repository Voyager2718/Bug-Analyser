#include"BugAnalyser.Interface.h"

BugAnalyserInterface& BugAnalyserInterface::add_analyst(shared_ptr< BugAnalyserInterface >(*analyst)( vector< string > )){
    analysts.push_back(analyst);
    return *this;
}