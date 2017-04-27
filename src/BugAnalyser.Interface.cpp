#include<exception>
#include<iostream>
#include<fstream>
#include"BugAnalyser.Interface.h"

BugAnalyserInterface& BugAnalyserInterface::add_analyst(shared_ptr< BugAnalyserInterface >(*analyst)( vector< string > )){
    analysts.push_back(analyst);
    return *this;
}

BugAnalyserInterface& BugAnalyserInterface::add_analyst(vector< shared_ptr< BugAnalyserInterface >(*)( vector< string > ) > analysts){
    this->analysts = analysts;
    return *this;
}

shared_ptr<Report> BugAnalyserInterface::analyse_log(string bug_log_location) {
    std::ifstream in_file(bug_log_location);

    if (in_file.is_open())
    {
        std::vector<std::string> lines_in_reverse;
        std::string line;
        while (std::getline(in_file, line))
        {
            // Store the lines in reverse order.
            lines_in_reverse.insert(lines_in_reverse.begin(), line);
        }//FIXME: Cause significant RAM usage, this problem must be fixed. But for quick test, that's fine. Move file pointer to trace from back.

        shared_ptr<Report> report(new Report());
        map< string, string >m_temp;
        m_temp["tree"] = analyser_name + " is running on " + bug_log_location;
        report->add_report(m_temp);//Add to report trace tree.
        
        for(int i = 0; i < lines_in_reverse.size(); i += 3){
            for(auto& analyst : analysts){
                vector<string> v_temp;
                v_temp.push_back(lines_in_reverse[i]);
                v_temp.push_back(lines_in_reverse[i+1]);
                v_temp.push_back(lines_in_reverse[i+2]);

                shared_ptr< BugAnalyserInterface > s_temp = analyst(v_temp);
                s_temp->add_analyst(this->analysts);
                if(s_temp != nullptr){
                    shared_ptr<Report> r_temp = s_temp->analyse_log();
                    
                }
            }
        }
        return report;
    }
    throw std::exception();
}

shared_ptr<Report> BugAnalyserInterface::analyse_log() {
    if(this->_bug_log_location == ""){
        throw std::exception(); //TODO: Better to introduce a bunch of Exception class or create an Exception class with message.
    }
    shared_ptr<Report> report(new Report());
    map< string, string >temp;
    temp["tree"] = analyser_name + " is running on " + this->_bug_log_location;
    //TODO: Add for all analysers.
    return report;
}