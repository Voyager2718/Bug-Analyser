#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class AnalyserFSM{
private:
    enum STATE  {CLASS_KEY_STATE, CLASSNAME_STATE, COLON_STATE, VIRTUAL_STATE, PERMISSION_STATE, NORMAL_STATE, FAILED, SUCCESS};
    // enum WORD   {OTHER, END_OF_FILE, CLASS_KEY, VALID_CLASS_NAME, COLON_KEY, VIRTUAL_KEY, PERMISSION_KEY, VALID_BASE_CLASS_NAME};
    STATE state;

    int code_position; // Interpreted position
    string code;

    int result; // 0: Failed 1: Success
    string class_name; // Extracted derived class name.

    vector< map< string, string > > tokens;

    map<string, string> make_map(string key, string value){
        map<string, string> temp;
        temp["keyword"] = key;
        temp["value"] = value;
        return temp;
    }

    bool is_cpp_keyword(string test){
        vector<string> keywords = {
            "alignas","alignof","and","and_eq","asm","atomic_cancel","atomic_commit","atomic_noexcept","auto","bitand","bitor","bool","break","case","catch","char","char16_t","char32_t","class","compl","concept","const","constexpr","const_cast","continue","decltype","default","delete","do","double","dynamic_cast","else","enum","explicit","export","extern","false","float","for","friend","goto","if","import","inline","int","long","module","mutable","namespace","new","noexcept","not","not_eq","nullptr","operator","or","or_eq","private","protected","public","register","reinterpret_cast","requires","return","short","signed","sizeof","static","static_assert","static_cast","struct","switch","synchronized","template","this","thread_local","throw","true","try","typedef","typeid","typename","union","unsigned","using","virtual","void","volatile","wchar_t","while","xor","xor_eq"
        };
        if(find(keywords.begin(), keywords.end(), test) != keywords.end()){
            return true;
        }
        return false;
    }

    void space_tokenizer(){
        while(1){
            if(code.substr(code_position, 1) == " "){
                code_position ++;
            }else{
                break;
            }
        }
    }

    void enter_tokenizer(){
        while(1){
            if(code.substr(code_position, 2) == "\r\n"){
                code_position += 2;
            }else if((code.substr(code_position, 1) == "\n")){
                code_position += 1;
            }else{
                break;
            }
        }
    }

    bool is_end_of_file_tokenizer(){
        if(code_position >= code.size()){
            return true;
        }
        return false;
    }

    bool is_class_tokenizer(){
        if(code.substr(code_position, 6) == "class "){
            code_position += 6;
            tokens.push_back(make_map("class_key", "\"class\""));
            return true;
        }
        return false;
    }

    bool is_valid_classname_tokenizer(){      
        if(is_cpp_keyword(code.substr(code_position, 4))){
            return false;
        }
        tokens.push_back(make_map("class_identifier", "\"" + string(code.substr(code_position, 4)) + "\""));
        code_position += 4; // FIXME
        return true;
    }

    bool is_colon_tokenizer(){
        if(code.substr(code_position, 1) == ":"){
            code_position ++;
            tokens.push_back(make_map("colon_key", "\":\""));
            return true;
        }
        return false;
    }

    bool is_virtual_tokenizer(){
        if(code.substr(code_position, 8) == "virtual "){
            code_position += 8;
            tokens.push_back(make_map("virtual_identifier", "\"virtual\""));
            return true;
        }
        return false;
    }

    bool is_permission_tokenizer(){
        if(code.substr(code_position, 7) == "public "){
            code_position += 7;
            tokens.push_back(make_map("permission_identifier", "\"public\""));
            return true;
        }else if(code.substr(code_position, 10) == "protected "){
            code_position += 10;
            tokens.push_back(make_map("permission_identifier", "\"protected\""));
            return true;
        }else if(code.substr(code_position, 8) == "private "){
            code_position += 8;
            tokens.push_back(make_map("permission_identifier", "\"private\""));
            return true;
        }
        return false;
    }

    bool is_normal_tokenizer(){
        //TODO: Ignore not wanted objects.
        code_position ++;
        return true;
    }

public:
    AnalyserFSM(string code){
        state = NORMAL_STATE;
        code_position = 0;
        this->code = code;

        while(1){
            STATE last_state = state;
            switch(state){
                case NORMAL_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_class_tokenizer()){
                        state = CLASS_KEY_STATE;
                    }else if(is_normal_tokenizer()){
                        
                    }
                    break;
                case CLASS_KEY_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_valid_classname_tokenizer()){
                        state = CLASSNAME_STATE;
                    }else if(is_end_of_file_tokenizer()){
                        state = FAILED;
                    }else{
                        state = NORMAL_STATE;
                    }
                    break;
                case CLASSNAME_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_colon_tokenizer()){
                        state = COLON_STATE;
                    }else{
                        state = NORMAL_STATE;
                    }
                    break;
                case COLON_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_virtual_tokenizer()){
                        state = VIRTUAL_STATE;
                    }else if(is_permission_tokenizer()){
                        state = PERMISSION_STATE;
                    }else if(is_valid_classname_tokenizer()){
                        state = SUCCESS;
                    }else{
                        state = NORMAL_STATE;
                    }
                    break;
                case VIRTUAL_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_permission_tokenizer()){
                        state = PERMISSION_STATE;
                    }else if(is_valid_classname_tokenizer()){
                        state = SUCCESS;
                    }else{
                        state = NORMAL_STATE;
                    }
                    break;
                case PERMISSION_STATE:
                    if(is_end_of_file_tokenizer()){
                        state = FAILED;
                        break;
                    }
                    space_tokenizer();
                    enter_tokenizer();
                    if(is_valid_classname_tokenizer()){
                        state = SUCCESS;
                    }else{
                        state = NORMAL_STATE;
                    }
                    break;
                case FAILED:
                    tokens = {};
                    result = 0;
                    return;
                case SUCCESS:
                    result = 1;
                    return;
            }
            if(last_state != NORMAL_STATE && state == NORMAL_STATE){
                tokens = {};
            }
        }
    }

    int get_result(){
        return result;
    }

    vector< map< string, string > > get_tokens(){
        return tokens;
    }
};

int main(int argc, char *argv[]){
    string code;
    if(argc > 1){
        // TODO: Get source code.
    }else{
        cout<<"Enter a code to parse:"<<endl;
        getline(cin, code);
        cout<<endl;
    }
    
    AnalyserFSM fsm(code);
    cout<<"Parse " + string(fsm.get_result() ? "success!" : "failed!")<<endl<<endl;;

    cout<<"Tokens:"<<endl;
    vector< map< string, string > > tokens = fsm.get_tokens();
    if(tokens.size() == 0){
        cout<<"No token has been generated because parsing failed."<<endl;
    }
    for(auto& token : tokens){
        cout<<token["keyword"]<<": "<<token["value"]<<endl;
    }
    return 0;
}