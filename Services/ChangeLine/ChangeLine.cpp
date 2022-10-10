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
void VerilogStudio::ChangeLine::AddPort(std::string &fileName,std::string& PortName,std::string& portEnd,std::string& sourceModule,int bracketsLocation,int endBracketsLocation) {
    OpenFile(fileName);
    if(FileContent.size()<bracketsLocation){
        cout << "error: add port out of range"<<endl;
    }
    string::size_type pos;
    string tempPortName;
    auto modulePos = FileContent.find(sourceModule);
    if(PortName.find("]")!=string::npos){
        auto tempPos = PortName.find("]");
        tempPortName = PortName.substr(tempPos+1);
    }else if(PortName.find("input")!=string::npos){
        auto tempPos = PortName.find("input");
        tempPortName = PortName.substr(tempPos+5);
    }else if(PortName.find("output")!=string::npos){
        auto tempPos = PortName.find("output");
        tempPortName = PortName.substr(tempPos+6);
    }else if(PortName.find("inout")!=string::npos) {
        auto tempPos = PortName.find("inout");
        tempPortName = PortName.substr(tempPos + 5);
    }
    if(portEnd == ";"){
        FileContent.insert(static_cast<string::size_type>(bracketsLocation+1),tempPortName + ",");
        modulePos = endBracketsLocation;
    }

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
    //cout <<"AddPort:"<<FileContent.substr(pos,pos+20)<<endl;
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::RemoveTopModule(std::string& TopModuleName,std::vector<std::string> &Vec) {
    auto ss = find_if(Vec.begin(),Vec.end(),[&](string& modulename){
        return modulename == TopModuleName;
    });
    if(ss!=Vec.end()){
        Vec.erase(ss);
    }
}

/**********************************************/
std::string VerilogStudio::ChangeLine::FlipPort(std::string &PortName) {
    if(PortName.find("input")!= string::npos){
        PortName.replace(PortName.find("input"), 5,"output");
    } else if(PortName.find("output")!= string::npos){
        PortName.replace(PortName.find("output"), 6,"input");
    }else if(PortName.find("inout")!= string::npos){
        return PortName;
    }
    return PortName;
}

/**********************************************/
void VerilogStudio::ChangeLine::AddInstPort(std::string &fileName, std::string &PortName,std::string &instModuleName) {
    if(fileName.empty())
        cout << "file name is empty." <<endl;
    string tempPortName;
    OpenFile(fileName);
    string::size_type pos;
    string DesPortName = PortName;
    if(fileName == TopModuleFileName){
        if(PortName.find("in_")!=string::npos){
            DesPortName.replace(DesPortName.find("in_"),3,"");
        } else if(PortName.find("out_")!=string::npos){
            DesPortName.replace(DesPortName.find("out_"),4,"");
        }
    }
    if(PortName.find("]")!=string::npos){
        auto tempPos = PortName.find("]");
        tempPortName = "."+PortName.substr(tempPos+1)+"("+DesPortName.substr(tempPos+1)+"),\n";
    }else if(PortName.find("input")!=string::npos){
        auto tempPos = PortName.find("input");
        tempPortName = "."+PortName.substr(tempPos+6)+"("+DesPortName.substr(tempPos+5)+"),\n";
    }else if(PortName.find("output")!=string::npos){
        auto tempPos = PortName.find("output");
        tempPortName = "."+PortName.substr(tempPos+7)+"("+DesPortName.substr(tempPos+6)+"),\n";
    }else if(PortName.find("inout")!=string::npos) {
        auto tempPos = PortName.find("inout");
        tempPortName = "." + PortName.substr(tempPos + 6) + "(" + DesPortName.substr(tempPos + 5) + "),\n";
    }
    if(FileContent.find(instModuleName)!= string::npos){
        if(FileContent.find("(",FileContent.find(instModuleName))!=string::npos)
            pos = FileContent.find("(",FileContent.find(instModuleName));
    }
    //cout <<"AddInstPort:"<<FileContent.substr(pos,pos+20)<<endl;
    FileContent.insert(pos+1,"\n        "+tempPortName);
    WriteFile(fileName);
}

/**********************************************/
void VerilogStudio::ChangeLine::AddToTopModule(std::string& fileName,std::string &PortName,std::string& portEnd,int bracketsLocation,int endBracketsLocation) {
    if(fileName.empty())
        cout << "file name is empty." <<endl;
    OpenFile(fileName);
    if(FileContent.size()<bracketsLocation){
        cout << "erroe:add top module out of range"<<endl;
    }
    if(PortName.find("input")!=string::npos){
        PortName.replace(PortName.find("input"), 5,"wire");
    }else if(PortName.find("output")!=string::npos){
        PortName.replace(PortName.find("output"), 6,"wire");
    }else if(PortName.find("inout")!=string::npos){
        PortName.replace(PortName.find("inout"), 5,"wire");
    }

    if(PortName.find("in_")!=string::npos){
        PortName.replace(PortName.find("in_"),3,"");
    }else if(PortName.find("out_")!=string::npos){
        PortName.replace(PortName.find("out_"),4,"");
    }
//    cout << "bracketsLocation:" <<FileContent.substr(bracketsLocation,bracketsLocation+20);
//    cout << "endBracketsLocation:"<<FileContent.substr(endBracketsLocation,endBracketsLocation+20)<<endl;
    if (portEnd == ";") {
        FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), PortName + ",\n    ");
    }
    FileContent.insert(static_cast<string::size_type>(bracketsLocation + 1), "\n    "+PortName + portEnd);
    WriteFile(fileName);
}

void VerilogStudio::ChangeLine::GetTopModuleName(std::string &TMFN) {
    TopModuleFileName = TMFN;
}


