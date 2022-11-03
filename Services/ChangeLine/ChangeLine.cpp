//
// Created by 狂飙的西红柿 on 2022/8/31.
//

#include "ChangeLine.hpp"

/**********************************************/
void VerilogStudio::ChangeLine::OpenFile(std::string &fileName) {
    ifstream in(fileName);
    stringstream buf;
    buf << in.rdbuf();
    FileContent = buf.str();
    in.close();
}

/**********************************************/
void VerilogStudio::ChangeLine::WriteFile(std::string &fileName) {
    ofstream ou(fileName);
    ou << FileContent;
    ou.close();
}

/**********************************************/
void VerilogStudio::ChangeLine::AddPort(std::string &fileName, std::string &PortName, std::string &portEnd, std::string &sourceModule, int bracketsLocation, int endBracketsLocation) {
    OpenFile(fileName);
    if (FileContent.size() < bracketsLocation) {
//        logger->error("function AddPort fadd port out of range.");
        cerr << "error: add port out of range" << endl;
    }
    string::size_type pos;
    string tempPortName;
    auto modulePos = FileContent.find(sourceModule);
    if (PortName.find("]") != string::npos) {
        auto tempPos = PortName.find("]");
        tempPortName = PortName.substr(tempPos + 1);
    } else if (PortName.find("input") != string::npos) {
        auto tempPos = PortName.find("input");
        tempPortName = PortName.substr(tempPos + 5);
    } else if (PortName.find("output") != string::npos) {
        auto tempPos = PortName.find("output");
        tempPortName = PortName.substr(tempPos + 6);
    } else if (PortName.find("inout") != string::npos) {
        auto tempPos = PortName.find("inout");
        tempPortName = PortName.substr(tempPos + 5);
    }
    cout << "tempPortName:" << tempPortName << endl;
    if (portEnd == ";") {
        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), tempPortName + ",");
        modulePos = endBracketsLocation;
    }

    if (PortName.find("input", modulePos) != string::npos) {
        pos = FileContent.find("input", modulePos);
    } else if (PortName.find("output", modulePos) != string::npos) {
        pos = FileContent.find("output", modulePos);
    } else if (PortName.find("inout", modulePos) != string::npos) {
        pos = FileContent.find("inout", modulePos);
    } else {
        pos = FileContent.find("input", modulePos);
    }
    if (portEnd == ";") {
        FileContent.insert(pos, PortName + portEnd + "\n    ");
    } else {
        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), PortName + portEnd + "\n    ");
    }

    //cout <<"AddPort:"<<FileContent.substr(pos,pos+20)<<endl;
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::RemoveTopModule(std::string &TopModuleName, std::vector<std::string> &Vec) {
    auto ss = find_if(Vec.begin(), Vec.end(), [&](string &modulename) {
        return modulename == TopModuleName;
    });
    if (ss != Vec.end()) {
        Vec.erase(ss);
    }
}

/**********************************************/
std::string VerilogStudio::ChangeLine::FlipPort(std::string &PortName) {
    if (PortName.find("input") != string::npos) {
        PortName.replace(PortName.find("input"), 5, "output");
    } else if (PortName.find("output") != string::npos) {
        PortName.replace(PortName.find("output"), 6, "input");
    } else if (PortName.find("inout") != string::npos) {
        return PortName;
    }
    return PortName;
}

/**********************************************/
void VerilogStudio::ChangeLine::AddInstPort(std::string &fileName, std::string &PortName, std::string &instModuleName) {
    if (fileName.empty()) {
        cerr << "function AddInstPort file name is empty." << endl;
//        logger->error("function AddInstPort file name is empty.");
    }
    string tempPortName;
    OpenFile(fileName);
    string::size_type pos;
    string DesPortName = PortName;
    if (fileName == TopModuleFileName) {
        if (PortName.find("in_") != string::npos) {
            DesPortName.replace(DesPortName.find("in_"), 3, "");
        } else if (PortName.find("out_") != string::npos) {
            DesPortName.replace(DesPortName.find("out_"), 4, "");
        }
    }
    if (PortName.find("]") != string::npos) {
        auto tempPos = PortName.find("]");
        tempPortName = "." + PortName.substr(tempPos + 1) + "(" + DesPortName.substr(tempPos + 1) + "),\n";
    }else if (PortName.find("input") != string::npos) {
        auto tempPos = PortName.find("input");
        tempPortName = "." + PortName.substr(tempPos + 6) + "(" + DesPortName.substr(tempPos + 5) + "),\n";
    } else if (PortName.find("output") != string::npos) {
        auto tempPos = PortName.find("output");
        tempPortName = "." + PortName.substr(tempPos + 7) + "(" + DesPortName.substr(tempPos + 6) + "),\n";
    } else if (PortName.find("inout") != string::npos) {
        auto tempPos = PortName.find("inout");
        tempPortName = "." + PortName.substr(tempPos + 6) + "(" + DesPortName.substr(tempPos + 5) + "),\n";
    }
    if (FileContent.find(instModuleName) != string::npos) {
        if (FileContent.find("(", FileContent.find(instModuleName)) != string::npos)
            pos = FileContent.find("(", FileContent.find(instModuleName));
    }
    //cout <<"AddInstPort:"<<FileContent.substr(pos,pos+20)<<endl;
    FileContent.insert(pos + 1, "\n        " + PortName);
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::AddToTopModule(std::string &fileName, std::string &PortName, std::string &portEnd, int bracketsLocation, int endBracketsLocation) {
    if (fileName.empty()) {
        //logger->error("function AddToTopModule file name is empty.");
        cerr << "function AddToTopModule file name is empty." << endl;
    }
    OpenFile(fileName);
    if (FileContent.size() < bracketsLocation) {
//        logger->error("function AddToTopModule add top module out of range.");
        cerr << "add top module out of range." << endl;
    }
    if (PortName.find("input") != string::npos) {
        PortName.replace(PortName.find("input"), 5, "wire");
    } else if (PortName.find("output") != string::npos) {
        PortName.replace(PortName.find("output"), 6, "wire");
    } else if (PortName.find("inout") != string::npos) {
        PortName.replace(PortName.find("inout"), 5, "wire");
    }

    if (PortName.find("in_") != string::npos) {
        PortName.replace(PortName.find("in_"), 3, "");
    } else if (PortName.find("out_") != string::npos) {
        PortName.replace(PortName.find("out_"), 4, "");
    }
//    cout << "bracketsLocation:" <<FileContent.substr(bracketsLocation,bracketsLocation+20);
//    cout << "endBracketsLocation:"<<FileContent.substr(endBracketsLocation,endBracketsLocation+20)<<endl;

//    if (portEnd == ";") {
//        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), PortName + ",\n    ");
//    }
    FileContent.insert(static_cast<string::size_type>(endBracketsLocation + 1), "\n    " + PortName + ";\n");
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::GetTopModuleName(std::string &TMFN) {
    TopModuleFileName = TMFN;
}

/**********************************************/
std::string VerilogStudio::ChangeLine::GetGroupPortName(std::string &sourceFileName,std::string& group) {
    if (sourceFileName.empty()) {
        //logger->error("function GetGroupPortName file name is empty.");
        cerr << "function GetGroupPortName file name is empty." << endl;
    }
    OpenFile(sourceFileName);
    size_t groupPos = FileContent.find("//"+group);
    size_t endGroupPos = FileContent.find("//end "+ group);
    auto dis = endGroupPos-(groupPos+ group.length()+2);
    return FileContent.substr(groupPos+group.length()+2,dis);
}

/**********************************************/
std::vector<std::string> VerilogStudio::ChangeLine::GetPortName(std::vector<std::string> portGather) {
    vector<string> PortNameGather;
    for(auto &it:portGather){
        string tempLeftPortName;
        if (it.find("]") != string::npos) {
            auto tempPos = it.find("]");
            tempLeftPortName = it.substr(tempPos + 1);
        } else if(it.find("wire") != string::npos){
            auto tempPos = it.find("wire");
            tempLeftPortName = it.substr(tempPos + 4);
        }else if (it.find("input") != string::npos) {
            auto tempPos = it.find("input");
            tempLeftPortName = it.substr(tempPos + 5);
        } else if (it.find("output") != string::npos) {
            auto tempPos = it.find("output");
            tempLeftPortName = it.substr(tempPos + 6);
        } else if (it.find("inout") != string::npos) {
            auto tempPos = it.find("inout");
            tempLeftPortName = it.substr(tempPos + 5);
        }
        PortNameGather.emplace_back(tempLeftPortName);
    }
    return PortNameGather;
}

/**********************************************/
std::string &VerilogStudio::ChangeLine::Trim(string &str) {

    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

/**********************************************/
std::string VerilogStudio::ChangeLine::InstGroupPortName(std::string &fileName,std::vector<std::string> &portNameGather) {
    string tempPortNameGather;
    for(auto&it : portNameGather){
        if(!it.empty()){
            string tempInstPortName = Trim(it);
            if (fileName == TopModuleFileName) {
                if (tempInstPortName.find("in_") != string::npos) {
                    tempInstPortName.replace(tempInstPortName.find("in_"), 3, "");
                } else if (tempInstPortName.find("out_") != string::npos) {
                    tempInstPortName.replace(tempInstPortName.find("out_"), 4, "");
                }
            }
            cout << Trim(it) <<endl;
            cout << Trim(it).substr(0,Trim(it).find(",")) <<endl;
            if(tempInstPortName.find(",")!=string::npos){
                tempPortNameGather=tempPortNameGather+"."+Trim(it).substr(0,Trim(it).find(","))+"("+tempInstPortName.substr(0,tempInstPortName.find(","))+"),\n        ";
            }else if(Trim(it).find(";")!=string::npos){
                tempPortNameGather=tempPortNameGather+"."+Trim(it).substr(0,Trim(it).find(";"))+"("+tempInstPortName.substr(0,tempInstPortName.find(";"))+"),\n        ";
            }
        }
    }
    return tempPortNameGather;
}

/**********************************************/
void VerilogStudio::ChangeLine::AddGroupPort(std::string &fileName, std::vector<std::string> &portGather,std::string &portEnd, std::string &sourceModule, int bracketsLocation, int endBracketsLocation) {
    OpenFile(fileName);
    if (FileContent.size() < bracketsLocation) {
//        logger->error("function AddPort fadd port out of range.");
        cerr << "error: add port out of range" << endl;
    }
    if(portGather.empty()||portGather.size()<1){
        cerr << "portname is empty" <<endl;
    }

    string::size_type pos;

    auto modulePos = FileContent.find(sourceModule);
//    string tempPortName;
//    for(auto &it:portName){
//        if(!it.empty()){
//            tempPortName += Trim(it);
////            if (Trim(it).find("]") != string::npos) {
////                auto tempPos = Trim(it).find("]");
////                tempPortName = tempPortName + Trim(it).substr(tempPos + 1);
////            } else if (Trim(it).find("input") != string::npos) {
////                auto tempPos = Trim(it).find("input");
////                tempPortName = tempPortName+Trim(it).substr(tempPos + 5);
////            } else if (Trim(it).find("output") != string::npos) {
////                auto tempPos = Trim(it).find("output");
////                tempPortName = tempPortName+Trim(it).substr(tempPos + 6);
////            } else if (Trim(it).find("inout") != string::npos) {
////                auto tempPos = Trim(it).find("inout");
////                tempPortName = tempPortName + Trim(it).substr(tempPos + 5);
////            }
//        }
//    }

    cout << "tempPortName:" << portGather[0] << endl;
    if (portEnd == ";") {
        //FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), portGather[0]);
        modulePos = endBracketsLocation;
    }

    if (FileContent.find("input", modulePos) != string::npos) {
        pos = FileContent.find("input", modulePos);
    } else if (FileContent.find("output", modulePos) != string::npos) {
        pos = FileContent.find("output", modulePos);
    } else if (FileContent.find("inout", modulePos) != string::npos) {
        pos = FileContent.find("inout", modulePos);
    } else {
        pos = FileContent.find("input", modulePos);
    }

    if (portEnd == ";") {
//        string temp_port_name;
//        for(auto &it:portTypeNameGather){
//            if(!it.empty()){
//                temp_port_name += Trim(it).replace(Trim(it).find(","), 3, ";\n    ");
//            }
//        }
        FileContent.insert(pos, portGather[1] + "\n    ");
    } else {
//        string temp_port_name;
//        for(auto &it:portTypeNameGather){
//            if(!it.empty()){
//                temp_port_name += Trim(it)+"\n     ";
//            }
//        }
        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), portGather[1] + "\n    ");
    }

    //cout <<"AddPort:"<<FileContent.substr(pos,pos+20)<<endl;
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::AddGroupToTopModule(std::string &fileName, std::vector<std::string> &portNameGather, std::string &portEnd, int bracketsLocation, int endBracketsLocation) {
    if (fileName.empty()) {
        //logger->error("function AddToTopModule file name is empty.");
        cerr << "function AddToTopModule file name is empty." << endl;
    }
    string PortName;
    OpenFile(fileName);
    if (FileContent.size() < bracketsLocation) {
//        logger->error("function AddToTopModule add top module out of range.");
        cerr << "add top module out of range." << endl;
    }
    for(auto &it :portNameGather){
        string temp_str;
        if(!it.empty()){
            temp_str = "wire "+Trim(it);
//            if (Trim(it).find("input") != string::npos) {
//                Trim(it).replace(Trim(it).find("input"), 5, "wire");
//            } else if (Trim(it).find("output") != string::npos) {
//                Trim(it).replace(Trim(it).find("output"), 6, "wire");
//            } else if (Trim(it).find("inout") != string::npos) {
//                Trim(it).replace(Trim(it).find("inout"), 5, "wire");
//            }

        }

        if (temp_str.find("in_") != string::npos) {
            temp_str.replace(temp_str.find("in_"), 3, "");
        } else if (Trim(it).find("out_") != string::npos) {
            temp_str.replace(temp_str.find("out_"), 4, "");
        }

        if(temp_str.find(",")!=string::npos){
            temp_str.replace(temp_str.find(","), 1, ";");
        }
        PortName = PortName+temp_str+"\n    ";
    }

//    cout << "bracketsLocation:" <<FileContent.substr(bracketsLocation,bracketsLocation+20);
//    cout << "endBracketsLocation:"<<FileContent.substr(endBracketsLocation,endBracketsLocation+20)<<endl;

//    if (portEnd == ";") {
//        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), PortName + ",\n    ");
//    }
    FileContent.insert(static_cast<string::size_type>(endBracketsLocation + 1), "\n    " + PortName);
    WriteFile(fileName);
}

std::vector<std::string> VerilogStudio::ChangeLine::ComposeGroupPortName(std::vector<std::string> &portTypeNameGather, std::vector<std::string> &portName, std::string &portEnd) {
    string tempPortName,temp_port_name;
    vector<string> tempPortGather;
    for(auto &it:portName){
        if(!Trim(it).empty()){
            tempPortName += Trim(it);
        }
    }

    if (portEnd == ";") {
        for(auto &it:portTypeNameGather){
            if(!Trim(it).empty()){
                temp_port_name += Trim(it).replace(Trim(it).find(","), 3, ";\n    ");
            }
        }
    } else {
        for(auto &it:portTypeNameGather){
            if(!Trim(it).empty()){
                temp_port_name += Trim(it)+"\n     ";
            }
        }
    }
    tempPortGather.emplace_back(tempPortName);
    tempPortGather.emplace_back(temp_port_name);

    return tempPortGather;
}

