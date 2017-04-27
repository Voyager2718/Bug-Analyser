#include<iostream>
#include"src/GeneralBugAnalyser.h"

using std::cout;
using std::cin;

int main(int argc, char *argv[]){
    GeneralBugAnalyser analyser;
    analyser.add_analyst(GeneralBugAnalyser::analyse);
    shared_ptr<Report> report = analyser.analyse_log("./inst.log");
    
    return 0;
}