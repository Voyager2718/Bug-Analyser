#include<exception>
#include<iostream>
#include<fstream>
#include"BugAnalyser.Abstract.h"

BugAnalyserAbstract::BugAnalyserAbstract(){}

BugAnalyserAbstract& BugAnalyserAbstract::add_analyst(shared_ptr< BugAnalyserAbstract >(*analyst)( vector< string > )){
    analysts.push_back(analyst);
    return *this;
}

BugAnalyserAbstract& BugAnalyserAbstract::add_analyst(vector< shared_ptr< BugAnalyserAbstract >(*)( vector< string > ) > analysts){
    this->analysts = analysts;
    return *this;
}

shared_ptr<Report> BugAnalyserAbstract::analyse_log(string bug_log_location) {
    std::ifstream in_file(bug_log_location);

    if (in_file.is_open())
    {
        std::vector<std::string> log_lines;
        std::string line;
        
        /* Maybe not using reverse order is better?
        while (std::getline(in_file, line))
        {
            // Store the lines in reverse order.
            lines_in_reverse.insert(lines_in_reverse.begin(), line);
        }//FIXME: Cost significant RAM usage, this problem must be fixed. But for quick test, that's fine. Move file pointer to trace from back.
        */

        while (std::getline(in_file, line))
        {
            // Store the lines in reverse order.
            log_lines.push_back(line);
        }//FIXME: Cost significant RAM usage, use file pointer istead. Only for test.

        shared_ptr<Report> report(new Report());
        map< string, string >m_temp;
        m_temp["tree"] = analyser_name + " is running on " + bug_log_location + ": Found an error.";
        std::cout<<analyser_name + " is running on " + bug_log_location + ": Found an error."<<std::endl;
        report->add_report(m_temp);//Add to report trace tree.
        
        for(int i = 0; i < log_lines.size(); i += 3){
            for(auto& analyst : analysts){
                vector<string> v_temp;
                v_temp.push_back(log_lines[i]);
                v_temp.push_back(log_lines[i+1]);
                v_temp.push_back(log_lines[i+2]);

                shared_ptr< BugAnalyserAbstract > s_temp = analyst(v_temp);
                s_temp->add_analyst(this->analysts);
                if(s_temp != nullptr){
                    shared_ptr<Report> r_temp = s_temp->analyse_log();
                    report->merge_reports(r_temp);
                }
            }
        }
        return report;
    }
    throw std::exception();
}

shared_ptr<Report> BugAnalyserAbstract::analyse_log() {
    std::ifstream in_file(this->_bug_log_location);

    if (in_file.is_open())
    {
        std::vector<std::string> log_lines;
        std::string line;
        
        /* Maybe not using reverse order is better?
        while (std::getline(in_file, line))
        {
            // Store the lines in reverse order.
            lines_in_reverse.insert(lines_in_reverse.begin(), line);
        }//FIXME: Cost significant RAM usage, this problem must be fixed. But for quick test, that's fine. Move file pointer to trace from back.
        */

        while (std::getline(in_file, line))
        {
            // Store the lines in reverse order.
            log_lines.push_back(line);
        }//FIXME: Cost significant RAM usage, use file pointer istead. Only for test.

        shared_ptr<Report> report(new Report());
        map< string, string >m_temp;
        m_temp["tree"] = analyser_name + " is running on " + this->_bug_log_location + ": Found an error.";
        std::cout<<analyser_name + " is running on " + this->_bug_log_location + ": Found an error."<<std::endl;
        report->add_report(m_temp);//Add to report trace tree.
        
        for(int i = 0; i < log_lines.size(); i += 3){
            for(auto& analyst : analysts){
                vector<string> v_temp;
                v_temp.push_back(log_lines[i]);
                v_temp.push_back(log_lines[i+1]);
                v_temp.push_back(log_lines[i+2]);

                shared_ptr< BugAnalyserAbstract > s_temp = analyst(v_temp);
                s_temp->add_analyst(this->analysts);
                if(s_temp != nullptr){
                    map< string, string >m_temp2;
                    m_temp2["err"] = analyser_name + " is running on " + this->_bug_log_location + ": Found an error.";
                    shared_ptr<Report> r_temp = s_temp->analyse_log();
                    report->merge_reports(r_temp);
                }
            }
        }
        return report;
    }
    throw std::exception();
}