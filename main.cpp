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

    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/g.json";
    vector<string> fileVec = {"test02.v","test03.v"};
    p->ReadJson(jsonname);
    for(auto& itr:fileVec){
        p->ParseVerilog(itr);
    }

    string topModule = "counter10";
    auto tr = h->CreateTree(topModule,p);
    h->ShowTree(tr);

    cout << p->GetFileName(topModule) <<endl;



//    string a = "counter10";
//    string b = "adder";
//    h->GetShortestPath(*tr.root,a,b);


    return 0;
}
