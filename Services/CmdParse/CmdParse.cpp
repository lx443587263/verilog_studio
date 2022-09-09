//
// Created by 狂飙的西红柿 on 2022/9/6.
//
#include "CmdParse.hpp"

void VerilogStudio::CmdParse::CmdLineParse(int argc, char **argv) {
    //string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/temp.json";
    shared_ptr<cmdline::parser> cmdparse = cmdline::parser::makeB_OBJ<cmdline::parser>();
    pParse = Parse::makeB_OBJ<Parse>();
    pHierarchy = Hierarchy::makeB_OBJ<Hierarchy>();
    pDraw = DrawTree::makeB_OBJ<DrawTree>();
    cmdparse->add("inter",'a',"command interaction");
    cmdparse->add<string>("input",'i',"input filename. example: [-i] <filename>", false, "");
    cmdparse->add<string>("filelist",'l',"input filelist. example: [-l] <filelist>",false,"");
    cmdparse->add<string>("top",'t',"top module. example: [-t] <modulename>",false,"");
    cmdparse->add("hierarchy",'h',"show hierarchy");
    cmdparse->parse_check(argc,argv);
    if(argc==1){
        cerr << cmdparse->usage();
    }

    if(cmdparse->exist("top")){
        TopModuleName = cmdparse->get<string>("top");
    }

    if(cmdparse->exist("input")){

    }

    if(cmdparse->exist("filelist")){
        ReadFileToVec(cmdparse->get<string>("filelist"));
        //ReadFileToVec("/Users/liuxi/CLionProjects/verilog_studio/file.list");
        FileNameStr();
        string JsonPath = CreateVerilogJson();
        if(JsonPath.empty()){
            cerr<<"JsonPath is empty"<<endl;
        }

        ThreadPool pool(4);
        pParse->ReadJson(JsonPath);

        pool.enqueue([&](){
            for(auto& itr:FileNameVec){
                pParse->ParseVerilog(itr);
            }
        });
    }

    if(cmdparse->exist("hierarchy")) {
        auto tr = pHierarchy->CreateTree(TopModuleName,pParse);
        pHierarchy->ShowTree(tr);
        pDraw->draw_rb(tr.root,"hierarchy.png");

    }

}

std::vector<std::string> VerilogStudio::CmdParse::ReadFileToVec(const std::string &FileList) {
    ifstream file(FileList, ios::in);
    if (!file.is_open())
        cout << "error" << endl;
    string s;
    while (file >> s)
        FileNameVec.emplace_back(s);
    return FileNameVec;
}

std::string VerilogStudio::CmdParse::FileNameStr() {
    for(auto& it:FileNameVec){
        AllFileName =  AllFileName+" "+it;
    }
    return AllFileName;
}

std::string VerilogStudio::CmdParse::GetENV() {
    string VeribleENV;
    VeribleENV = getenv("VERIBLE_HOME");
    return VeribleENV;
}

std::string VerilogStudio::CmdParse::CreateVerilogJson() {
    string temp = GetENV();
    temp = temp + "/verible-verilog-syntax --printtree "+AllFileName + " --export_json > temp.json";
    system(temp.c_str());
    temp = GetJsonPath();
    temp = temp.substr(0,temp.size()-1) + "/temp.json";
    return temp;
}

std::string VerilogStudio::CmdParse::GetJsonPath() {
    FILE *fp = nullptr;
    char PwdBuf[100] = {0};
    //string PwdBuf;
    fp = popen("pwd","r");
    if(fp){
        int ret = fread(PwdBuf,1, sizeof(PwdBuf)-1,fp);
        if(ret>0){
            return PwdBuf;
        }
        pclose(fp);
    }
    return PwdBuf;
}
