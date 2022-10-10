//
// Created by 狂飙的西红柿 on 2022/9/6.
//
#include "CmdParse.hpp"

/**********************************************/
void VerilogStudio::CmdParse::CmdLineParse(int argc, char **argv) {
    //string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/temp.json";
    shared_ptr<cmdline::parser> cmdparse = cmdline::parser::makeB_OBJ<cmdline::parser>();
    pParse = Parse::makeB_OBJ<Parse>();
    pHierarchy = Hierarchy::makeB_OBJ<Hierarchy>();
    pDraw = DrawTree::makeB_OBJ<DrawTree>();
    pChangeLine = ChangeLine::makeB_OBJ<ChangeLine>();
    cmdparse->footer("version:v2.1.7 2022-10-09");
    cmdparse->add("inter", 'a', "command interaction");
    cmdparse->add<string>("input", 'i', "input filename. example: [-i] <filename>", false, "");
    cmdparse->add<string>("filelist", 'l', "input filelist. example: [-l] <filelist>", false, "");
    cmdparse->add<string>("top", 't', "top module. example: [-t] <modulename>", false, "");
    cmdparse->add<string>("change", 'c', "change line. example: [-c] <change line filename>", false, "");
    cmdparse->add("je", 'j', "thread");
    cmdparse->add("hierarchy", 'h', "show hierarchy");
    cmdparse->parse_check(argc, argv);
    if (argc == 1) {
        cerr << cmdparse->usage();
    }

    if (cmdparse->exist("top")) {
        TopModuleName = cmdparse->get<string>("top");
    }
    if (cmdparse->exist("input")) {

        FileNameVec = {"/Users/liuxi/CLionProjects/verilog_studio/test/test02.v",
                       "/Users/liuxi/CLionProjects/verilog_studio/test/test03.v",
                       "/Users/liuxi/CLionProjects/verilog_studio/test/test04.v",
                       "/Users/liuxi/CLionProjects/verilog_studio/test/test05.v",
                       "/Users/liuxi/CLionProjects/verilog_studio/test/test06.v"};
        //FileNameVec = {"testdefine.v"};
        ThreadPool pool(4);
        string JsonPath = cmdparse->get<string>("input");
        pParse->ReadJson(JsonPath);

        pool.enqueue([&]() {
            for (auto &itr: FileNameVec) {
                pParse->ParseVerilog(itr);
            }
        });
    }
    if (cmdparse->exist("filelist")) {
        if (!FileNameVec.empty()) {
            FileNameVec.clear();
        }
        ReadFileToVec(cmdparse->get<string>("filelist")).swap(FileNameVec);
        //ReadFileToVec("/Users/liuxi/CLionProjects/verilog_studio/file.list");
        FileNameStr();
        string JsonPath = CreateVerilogJson();
        if (JsonPath.empty()) {
            cerr << "JsonPath is empty" << endl;
        }


        pParse->ReadJson(JsonPath);


        if (cmdparse->exist("je")) {
            ThreadPool pool(4);
            pool.enqueue([&]() {
                for (auto &itr: FileNameVec) {
                    pParse->ParseVerilog(itr);
                }
            });

        } else {
            for (auto &itr: FileNameVec) {
                pParse->ParseVerilog(itr);
            }
        }

    }
    if (cmdparse->exist("hierarchy")) {
        auto tr = pHierarchy->CreateTree(TopModuleName, pParse);
        pHierarchy->ShowTree(tr);
        pDraw->draw_rb(tr.root, "hierarchy.png");

    }
    if (cmdparse->exist("change")) {
        //change line file
        ReadFileToVec(cmdparse->get<string>("change")).swap(ChangeLineContent);

        for (auto &it: ChangeLineContent) {
            if (it.empty()) {
                continue;
            }
            AddLine(it);
        }
    }

}

/**********************************************/
std::vector<std::string> VerilogStudio::CmdParse::ReadFileToVec(const std::string &FileList) {
    ifstream file(FileList, ios::in);
    vector<string> temp;
    if (!file.is_open())
        cout << "error" << endl;
    string s;
    while (getline(file, s))
        temp.emplace_back(s);
    return temp;
}

/**********************************************/
std::string VerilogStudio::CmdParse::FileNameStr() {
    for (auto &it: FileNameVec) {
        AllFileName = AllFileName + " " + it;
    }
    return AllFileName;
}

/**********************************************/
std::string VerilogStudio::CmdParse::GetENV() {
    string VeribleENV;
    VeribleENV = getenv("VERIBLE_HOME");
    return VeribleENV;
}

/**********************************************/
std::string VerilogStudio::CmdParse::CreateVerilogJson() {
    string temp = GetENV();
    //string temp = "/home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin";
    temp += "/verible-verilog-syntax --printtree l" + AllFileName + " --export_json > temp.json";
    system(temp.c_str());
    temp = GetJsonPath();
    temp = temp.substr(0, temp.size() - 1) + "/temp.json";
    return temp;
}

/**********************************************/
std::string VerilogStudio::CmdParse::GetJsonPath() {
    FILE *fp = nullptr;
    char PwdBuf[100] = {0};
    //string PwdBuf;
    fp = popen("pwd", "r");
    if (fp) {
        int ret = fread(PwdBuf, 1, sizeof(PwdBuf) - 1, fp);
        if (ret > 0) {
            return PwdBuf;
        }
        pclose(fp);
    }
    return PwdBuf;
}

/**********************************************/
vector<string> VerilogStudio::CmdParse::split(const string &str, const string &delims) {
    std::vector<std::string> output;
    auto first = str.cbegin();

    while (first != str.cend()) {
        const auto second = std::find_first_of(first, str.cend(), delims.cbegin(), delims.cend());
        if (first != second)
            output.emplace_back(first, second);
        if (second == str.cend())
            break;

        first = std::next(second);
    }

    return output;
}

/**********************************************/
string &VerilogStudio::CmdParse::Trim(string &str) {

    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

/**********************************************/
void VerilogStudio::CmdParse::AddLine(string &connectRule) {
    auto tr = pHierarchy->CreateTree(TopModuleName, pParse);


    vector<string> tempPath = split(connectRule, "=>");
    cout << "tempath[0]:" << tempPath[0] << endl;
    cout << "tempath[1]:" << tempPath[1] << endl;
    //tempPath[1] = Trim(tempPath[1]);
    vector<string> path1 = split(tempPath[0], ".");
    vector<string> path2 = split(tempPath[1], ".");
    string leftPortName = path1.back();
    cout << "leftPortName:"<<leftPortName <<endl;
    string rightPortName = path2.back();
    cout << "rightPortName:"<<rightPortName<<endl;
    string PortName = leftPortName;
    cout << "portName:" <<PortName<<endl;

    if (rightPortName.find("input") != string::npos || rightPortName.find("output") != string::npos || rightPortName.find("inout") != string::npos) {
        path2.pop_back();
    } else {
        //rightPortName.clear();
        rightPortName = "No";
    };
    path1.pop_back();
    htree<string>::iterator iter(tr.root);
    cout <<"tree node"<<tr.root->ModuleName<<endl;
    for(auto &it:path1){
        pParse->GetSrcModuleName(iter,it,path1.back());
    }
    iter=tr.root;
    for(auto &it:path2){
        pParse->GetSrcModuleName(iter,it,path2.back());
    }

    vector<string> InstModuleNamePath = pHierarchy->MergePath(path1, path2);
    string FlipModule = pHierarchy->GetFlipModule();
    cout << "FlipModule:" << FlipModule << endl;
    string lastModuleName = InstModuleNamePath.back();
    cout << "lastModuleName:" << lastModuleName << endl;
    string virTopModule = pHierarchy->GetVirTopModule();
    //pParse->GetKVInstModule(InstModuleNamePath,virTopModule);
    pParse->ShowKvInstModule();
    cout << "virTopModule:" << virTopModule << endl;
    string getVirTopModuleFile = pParse->GetSourceFileName(virTopModule);
    cout << "getVirTopModuleFile:" << getVirTopModuleFile << endl;
    pChangeLine->GetTopModuleName(getVirTopModuleFile);

//    pChangeLine->RemoveTopModule(TopModuleName, InstModuleNamePath);
    for (auto &it: InstModuleNamePath) {
        cout << "InstModuleNamePath:" << it << endl;

        string tempSourceFileName = pParse->GetSourceFileName(it);
        cout << "tempSourceFileName:" << tempSourceFileName << endl;

        string tempPortEnd = pParse->GetPortEnd(it);
        cout << "tempPortEnd:" << tempPortEnd << endl;
        string tempSrcModule = pParse->GetSourceModuleName(it);
        cout << "tempSrcModule:" << tempSrcModule << endl;
        int tempBracketsLocation = pParse->GetBracketsLocation(it);
        cout << "tempBracketslocation:" << tempBracketsLocation << endl;
        int tempEndBracketsLocation = pParse->GetEndBracketsLocation(it);
        string tempInstFileName = pParse->GetInstLocationFileName(it);
        cout << "tempInstFileName:" << tempInstFileName << endl;
        if (it == virTopModule) {
            pChangeLine->AddToTopModule(tempSourceFileName, PortName, tempPortEnd, tempBracketsLocation, tempEndBracketsLocation);
        } else {
            if (it == FlipModule) {
                if (rightPortName == "No") {
                    PortName = pChangeLine->FlipPort(leftPortName);
                } else {
                    PortName = rightPortName;
                }
            }
            pChangeLine->AddPort(tempSourceFileName, PortName, tempPortEnd, tempSrcModule, tempBracketsLocation, tempEndBracketsLocation);
            pChangeLine->AddInstPort(tempInstFileName, PortName, it);
        }

    }

}


