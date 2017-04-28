#include<iostream>
#include"src/GeneralBugAnalyser.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char *argv[]){
    GeneralBugAnalyser analyser;
    analyser.add_analyst(GeneralBugAnalyser::analyse);
    if(argc <= 1){
        cout<<"Enter a log path to analyse:"<<endl;
        string path;
        cin>>path;
        shared_ptr<Report> report = analyser.analyse_log(path);
    }else{
        shared_ptr<Report> report = analyser.analyse_log(argv[1]);
    }
    return 0;
}