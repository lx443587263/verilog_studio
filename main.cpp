#include <iostream>
#include "rapidjson/filereadstream.h"
#include "./Services/Parse/Parse.hpp"


using namespace std;
using namespace rapidjson;
using namespace VerilogStudio;


int main(int argc,char* argv[]) {
    shared_ptr<Parse> p = Parse::makeB_OBJ<Parse>();
    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/c.json";
    vector<string> fileVec = {"test01.v","led_demo.v"};
    p->ReadJson(jsonname);
    //string filename ="test01.v";
    for(auto& itr:fileVec){
        p->ParseVerilog(itr);
    }

    
    return 0;
}
