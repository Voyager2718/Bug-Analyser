#include<vector>
#include<iostream>

using namespace std;

class Test{
private:
    vector<int> list;
    int _a = 100;
public:
    void add(int a){
        list.push_back(a);
    }
    vector<int> get_list(){
        return list;
    }
    int& get_a(){
        _a = 300;
        return _a;
    }
};

class Test2{
private:
    vector<int> list;
public:
    Test2& addInt(int a){
        list.push_back(a);
        return *this;
    }
    vector<int> getList(){
        return list;
    }
};

int main(){
    Test test;
    test.add(1);
    test.add(2);
    test.add(3);
    vector<int>list = test.get_list();
    list[1] = 10;
    cout<<list[1]<<" "<<(test.get_list())[1]<<endl;
    int a = test.get_a();
    a = 200;
    cout<<a<<" "<<test.get_a()<<endl;

    cout<<"----"<<endl;
    
    Test2 test2;
    test2.addInt(10)
        .addInt(20)
        .addInt(30);

    for(auto& i : test2.getList()){
        cout<<i<<endl;
    }


    return 0;
}