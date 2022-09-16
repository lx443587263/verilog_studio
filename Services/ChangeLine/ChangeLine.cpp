//
// Created by 狂飙的西红柿 on 2022/8/31.
//

#include "ChangeLine.hpp"

void VerilogStudio::ChangeLine::OpenFile(std::string &fileName) {
    ifstream in(fileName);
    stringstream buf;
    buf << in.rdbuf();
    FileContent = buf.str();
    in.close();
}

void VerilogStudio::ChangeLine::RegexReplace(std::string &srcStr, std::string &desStr) {
    regex pattern(srcStr);
    regex_replace(FileContent,pattern,desStr);
}

void VerilogStudio::ChangeLine::WriteFile(std::string &fileName) {
    ofstream ou(fileName);
    ou << FileContent;
    ou.close();
}

void VerilogStudio::ChangeLine::AddPort(std::string &fileName,std::string& PortName,std::string& portEnd,std::string& sourceModule) {
    OpenFile(fileName);
    string::size_type pos;
    auto modulePos = FileContent.find(sourceModule);
    if(PortName.find("input",modulePos)!= string::npos){
        pos = FileContent.find("input",modulePos);
    } else if(PortName.find("output",modulePos)!= string::npos){
        pos = FileContent.find("output",modulePos);
    }else if(PortName.find("inout",modulePos)!= string::npos){
        pos = FileContent.find("inout",modulePos);
    }else{
        pos = FileContent.find("input",modulePos);
    }
    FileContent.insert(pos,PortName + portEnd+"\n    ");
    WriteFile(fileName);
}

void VerilogStudio::ChangeLine::RemoveTopModule(std::string& TopModuleName,std::vector<std::string> &Vec) {
    auto ss = find_if(Vec.begin(),Vec.end(),[&](string& modulename){
        return modulename == TopModuleName;
    });
    if(ss!=Vec.end()){
        Vec.erase(ss);
    }
}

std::string VerilogStudio::ChangeLine::FlipPort(std::string &PortName) {
    regex inputRe("input");
    regex outputRe("output");
    if(PortName.find("input")!= string::npos){
        PortName = regex_replace(PortName,inputRe,"output");
    } else if(PortName.find("output")!= string::npos){
        PortName = regex_replace(PortName,outputRe,"input");
    }else if(PortName.find("inout")!= string::npos){
        return PortName;
    }
    return PortName;
}

void VerilogStudio::ChangeLine::AddInstPort(std::string &fileName, std::string &PortName) {

}


