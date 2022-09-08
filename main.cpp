#include <iostream>
#include "./Services/CmdParse/CmdParse.hpp"
#include "./Services/DrawTree/DrawTree.hpp"

using namespace std;
using namespace rapidjson;
using namespace VerilogStudio;


int main(int argc,char* argv[]) {

    shared_ptr<CmdParse> pCmd = Parse::makeB_OBJ<CmdParse>();
    pCmd->CmdLineParse(argc,argv);

//    shared_ptr<Parse> p = Parse::makeB_OBJ<Parse>();
//    shared_ptr<Hierarchy> h = Hierarchy::makeB_OBJ<Hierarchy>();
//    shared_ptr<DrawTree> d = DrawTree::makeB_OBJ<DrawTree>();




//    string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/temp.json";
//    vector<string> fileVec =     {"/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test02.v",
//                                  "/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test03.v",
//                                  "/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test04.v",
//                                  "/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test05.v",
//                                  "/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test06.v"};
//    p->ReadJson(jsonname);
//    for(auto& itr:fileVec){
//        p->ParseVerilog(itr);
//    }
//
//    string topModule = "counter10";
//    auto tr = h->CreateTree(topModule,p);
//    h->ShowTree(tr);
//
//    p->GetFileName(topModule);
//
//    d->draw_rb(tr.root,"test.png");



//    string a = "counter10";
//    string b = "adder";
//    h->GetShortestPath(*tr.root,a,b);



    return 0;
}
