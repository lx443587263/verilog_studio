//
// Created by 狂飙的西红柿 on 2022/9/6.
//
#include "CmdParse.hpp"
#include <chrono>
#include <unistd.h>

/**********************************************/
void VerilogStudio::CmdParse::CmdLineParse(int argc, char **argv) {
    //string jsonname = "/Users/liuxi/CLionProjects/verilog_studio/temp.json";
    logger = spdlog::basic_logger_mt("verilog_studio", "logs/basic-log.txt");
    logger->info("welcome to verilog_stuio!");
    shared_ptr<cmdline::parser> cmdparse = cmdline::parser::makeB_OBJ<cmdline::parser>();
    pParse = Parse::makeB_OBJ<Parse>();
    pHierarchy = Hierarchy::makeB_OBJ<Hierarchy>();
    pDraw = DrawTree::makeB_OBJ<DrawTree>();
    pChangeLine = ChangeLine::makeB_OBJ<ChangeLine>();
    cmdparse->footer("version:v2.4");
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
        auto start = chrono::steady_clock::now();
        string JsonPath = cmdparse->get<string>("input");
        pParse->ReadJson(JsonPath);
        auto end = chrono::steady_clock::now();
        cout << "ReadJson use time:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;


        start = chrono::steady_clock::now();

        pool.enqueue([&]() {
            for (auto &itr: FileNameVec) {
                pParse->ParseVerilog(itr);
            }
        });
        end = chrono::steady_clock::now();
        cout << "ParseVerilog use time:" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
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
            logger->error("JsonPath is empty");
            cerr << "JsonPath is empty" << endl;
        }


        pParse->ReadJson(JsonPath);


        if (cmdparse->exist("je")) {
            ThreadPool pool(24);
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
    htree<string>::iterator iter(tr.root);
    vector<string> InstModuleNamePath;
    string PortName, leftPortName, rightPortName, virTopModule;
    if (connectRule.find("=>") != string::npos) {
        ToTopFlag = false;
        vector<string> tempPath = split(connectRule, "=>");
        //tempPath[1] = Trim(tempPath[1]);
        vector<string> path1 = split(tempPath[0], ".");
        vector<string> path2 = split(tempPath[1], ".");
        leftPortName = path1.back();
        rightPortName = path2.back();
        PortName = leftPortName;

        if (rightPortName.find("input") != string::npos || rightPortName.find("output") != string::npos || rightPortName.find("inout") != string::npos) {
            path2.pop_back();
        } else {
            //rightPortName.clear();
            rightPortName = "No";
        };
        path1.pop_back();
        if (tr.root->ModuleName.empty()) {
            logger->error("tree is empty");
//            cout << "tree is empty()" << endl;
        }
        for (auto &it: path1) {
            pParse->GetSrcModuleName(iter, it, path1.back());
        }
        iter = tr.root;
        for (auto &it: path2) {
            pParse->GetSrcModuleName(iter, it, path2.back());
        }
        InstModuleNamePath = pHierarchy->MergePath(path1, path2);
        virTopModule = pHierarchy->GetVirTopModule();

        cout << "tempath[0]:" << tempPath[0] << endl;
        cout << "tempath[1]:" << tempPath[1] << endl;
        cout << "leftPortName:" << leftPortName << endl;
        cout << "rightPortName:" << rightPortName << endl;
        cout << "portName:" << PortName << endl;
        logger->info("tempath[0]:{}", tempPath[0]);
        logger->info("tempath[1]:{}", tempPath[1]);
        logger->info("leftPortName:{}", leftPortName);
        logger->info("rightPortName:{}", rightPortName);
        logger->info("portName:{}", PortName);
    } else {
        ToTopFlag = true;
        cout << "root:" << tr.root->ModuleName << endl;
        vector<string> path1 = split(connectRule, ".");
        leftPortName = path1.back();
        logger->info("leftPortName:{}", leftPortName);
        pParse->AddTopModuleKV(TopModuleName, path1[0]);
        PortName = leftPortName;
        rightPortName = leftPortName;
        path1.pop_back();
        if (tr.root->ModuleName.empty()) {
            logger->error("tree is empty");
//            cout << "tree is empty" << endl;
        }
        for (auto &it: path1) {
            pParse->GetSrcModuleName(iter, it, path1.back());
        }
        path1.swap(InstModuleNamePath);
        virTopModule = InstModuleNamePath.at(0);
    }

    string FlipModule = pHierarchy->GetFlipModule();
    string lastModuleName = InstModuleNamePath.back();
    //pParse->GetKVInstModule(InstModuleNamePath,virTopModule);
    pParse->ShowKvInstModule();
    string getVirTopModuleFile = pParse->GetSourceFileName(virTopModule);
    pChangeLine->GetTopModuleName(getVirTopModuleFile);
    cout << "FlipModule:" << FlipModule << endl;
    cout << "lastModuleName:" << lastModuleName << endl;
    cout << "virTopModule:" << virTopModule << endl;
    cout << "getVirTopModuleFile:" << getVirTopModuleFile << endl;
    logger->info("FlipModule:{}", FlipModule);
    logger->info("lastModuleName:{}", lastModuleName);
    logger->info("virTopModule:{}", virTopModule);
    logger->info("getVirTopModuleFile:{}", getVirTopModuleFile);
    //pChangeLine->RemoveTopModule(TopModuleName, InstModuleNamePath);
    for (auto &it: InstModuleNamePath) {
        string tempSourceFileName = pParse->GetSourceFileName(it);
        string tempPortEnd = pParse->GetPortEnd(it);
        string tempSrcModule = pParse->GetSourceModuleName(it);
        int tempBracketsLocation = pParse->GetBracketsLocation(it);
        int tempEndBracketsLocation = pParse->GetEndBracketsLocation(it);
        string tempInstFileName = pParse->GetInstLocationFileName(it);
        if (ToTopFlag) {
            pChangeLine->AddPort(tempSourceFileName, PortName, tempPortEnd, tempSrcModule, tempBracketsLocation, tempEndBracketsLocation);
            if (it != virTopModule) {
                pChangeLine->AddInstPort(tempInstFileName, PortName, it);
            }
        } else {
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
//        spdlog::info("InstModuleNamePath:{}", it);
//        spdlog::info("tempSourceFileName:{}", tempSourceFileName);
//        spdlog::info("tempPortEnd:{}", tempPortEnd);
//        spdlog::info("tempSrcModule:{}", tempSrcModule);
//        spdlog::info("tempBracketslocation:{}", tempBracketsLocation);
//        spdlog::info("tempInstFileName:{}", tempInstFileName);
        cout << "\nInstModuleNamePath:" << it << endl;
        cout << "tempSourceFileName:" << tempSourceFileName << endl;
        cout << "tempPortEnd:" << tempPortEnd << endl;
        cout << "tempSrcModule:" << tempSrcModule << endl;
        cout << "tempBracketslocation:" << tempBracketsLocation << endl;
        cout << "tempInstFileName:" << tempInstFileName << endl;
        logger->info("InstModuleNamePath:{}", it);
        logger->info("tempSourceFileName:{}", tempSourceFileName);
        logger->info("tempPortEnd:{}", tempPortEnd);
        logger->info("tempSrcModule:{}", tempSrcModule);
        logger->info("tempBracketslocation:{}", tempBracketsLocation);
        logger->info("tempInstFileName:{}", tempInstFileName);
    }

}


