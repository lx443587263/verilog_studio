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
    pChangeLine = ChangeLine::makeB_OBJ<ChangeLine>();
    cmdparse->add("inter", 'a', "command interaction");
    cmdparse->add<string>("input", 'i', "input filename. example: [-i] <filename>", false, "");
    cmdparse->add<string>("filelist", 'l', "input filelist. example: [-l] <filelist>", false, "");
    cmdparse->add<string>("top", 't', "top module. example: [-t] <modulename>", false, "");
    cmdparse->add<string>("change", 'c', "change line. example: [-c] <change line filename>", false, "");
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
        ReadFileToVec(cmdparse->get<string>("filelist")).swap(FileNameVec);
        //ReadFileToVec("/Users/liuxi/CLionProjects/verilog_studio/file.list");
        FileNameStr();
        string JsonPath = CreateVerilogJson();
        if (JsonPath.empty()) {
            cerr << "JsonPath is empty" << endl;
        }

        ThreadPool pool(4);
        pParse->ReadJson(JsonPath);

        pool.enqueue([&]() {
            for (auto &itr: FileNameVec) {
                pParse->ParseVerilog(itr);
            }
        });
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
            vector<string> tempPath = split(it, "=>");
            //tempPath[1] = Trim(tempPath[1]);
            vector<string> path1 = split(tempPath[0], ".");
            vector<string> path2 = split(tempPath[1], ".");
            string portName = path1.back();
            path1.pop_back();
            vector<string> InstModuleNamePath = pHierarchy->MergePath(path1, path2);
            string FlipModule = pHierarchy->GetFlipModule();
            string lastModuleName = InstModuleNamePath.back();
            pChangeLine->RemoveTopModule(TopModuleName, InstModuleNamePath);
            for (auto &it: InstModuleNamePath) {
                if (it == FlipModule) {
                    portName = pChangeLine->FlipPort(portName);
                }
                string tempFileName = pParse->GetInstLocationFileName(it);
                string tempSourceFileName = pParse->GetSourceFileName(it);
                string tempPortEnd = pParse->GetPortEnd(it);
                string tempSrcModule = pParse->GetSourceModuleName(it);
                pChangeLine->AddPort(tempSourceFileName,portName,tempPortEnd,tempSrcModule);
            }
        }
    }

}

std::vector<std::string> VerilogStudio::CmdParse::ReadFileToVec(const std::string &FileList) {
    ifstream file(FileList, ios::in);
    vector<string> temp;
    if (!file.is_open())
        cout << "error" << endl;
    string s;
    while (file >> s)
        temp.emplace_back(s);
    return temp;
}

std::string VerilogStudio::CmdParse::FileNameStr() {
    for (auto &it: FileNameVec) {
        AllFileName = AllFileName + " " + it;
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
    temp += "/verible-verilog-syntax --printtree " + AllFileName + " --export_json > temp.json";
    system(temp.c_str());
    temp = GetJsonPath();
    temp = temp.substr(0, temp.size() - 1) + "/temp.json";
    return temp;
}

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

string &VerilogStudio::CmdParse::Trim(string &str) {

    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}
