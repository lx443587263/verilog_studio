#include <iostream>
#include "rapidjson/filereadstream.h"
#include "./Services/Parse/Parse.hpp"
#include "./Services/Hierarchy/Hierarchy.hpp"


using namespace std;
using namespace rapidjson;
using namespace VerilogStudio;


int main(int argc,char* argv[]) {
    shared_ptr<Parse> p = Parse::makeB_OBJ<Parse>();
    shared_ptr<Hierarchy> h = Hierarchy::makeB_OBJ<Hierarchy>();

    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/f.json";
    vector<string> fileVec = {"test01.v"};
    p->ReadJson(jsonname);
    for(auto& itr:fileVec){
        p->ParseVerilog(itr);
    }
    string topModule = "counter110";
    h->createTree(topModule,p);


    return 0;
}
