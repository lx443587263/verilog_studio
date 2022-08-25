#include <iostream>
#include "rapidjson/filereadstream.h"
#include "Parse/Parse.hpp"


using namespace std;
using namespace rapidjson;



int main(int argc,char* argv[]) {
    Parse p;
    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/1.json";
    vector<string> fileVec = {"test01.v","led_demo.v"};
    p.ReadJson(jsonname);
    //string filename ="test01.v";
    for(auto& itr:fileVec){
        p.ParseVerilog(itr);
    }




    return 0;
}
