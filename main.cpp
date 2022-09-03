#include <iostream>
#include "rapidjson/filereadstream.h"
#include "./Services/Parse/Parse.hpp"
#include "./Services/Hierarchy/Hierarchy.hpp"
#include "./Services/DrawTree/DrawTree.hpp"


using namespace std;
using namespace rapidjson;
using namespace VerilogStudio;


int main(int argc,char* argv[]) {
    shared_ptr<Parse> p = Parse::makeB_OBJ<Parse>();
    shared_ptr<Hierarchy> h = Hierarchy::makeB_OBJ<Hierarchy>();
    shared_ptr<DrawTree> d = DrawTree::makeB_OBJ<DrawTree>();

    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/j.json";
    vector<string> fileVec = {"test02.v","test03.v","test04.v"};
    p->ReadJson(jsonname);
    for(auto& itr:fileVec){
        p->ParseVerilog(itr);
    }

    string topModule = "counter10";
    auto tr = h->CreateTree(topModule,p);
    //h->ShowTree(tr);

    p->GetFileName(topModule);

    d->draw_rb(tr.root,"test.png");



//    string a = "counter10";
//    string b = "adder";
//    h->GetShortestPath(*tr.root,a,b);



    return 0;
}
