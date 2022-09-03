//
// Created by 狂飙的西红柿 on 2022/8/24.
//

#include "Module.hpp"



void VerilogStudio::Module::AddPortName(const string &PortName) {
    PortNameVec.emplace_back(PortName);
}

void VerilogStudio::Module::AddIncludeModuleName(vector<string> &UnInstModuleName, vector<string> &InstModuleName) {
    for (auto i = 0; i < UnInstModuleName.size(); ++i) {
        pair<string,string> temp= {UnInstModuleName[i],InstModuleName[i]};
        IncludeModuleNameUnMap.insert(temp);
    }
}

void VerilogStudio::Module::AddIncludeModuleNameMap(vector<string> &InstModuleName, vector<string> &UnInstModuleName) {
    for (auto i = 0; i < InstModuleName.size(); ++i) {
        pair<string,string> temp= {InstModuleName[i],UnInstModuleName[i]};
        IncludeModuleNameMap.insert(temp);
    }
}

void VerilogStudio::Module::AddParameter(vector<string> &ParameterName, vector<string> &ParameterValue) {
    for (auto i = 0; i < ParameterName.size(); ++i) {
        ParameterValueUnMap[ParameterName[i]] = ParameterValue[i];
    }
}

void VerilogStudio::Module::AddInstPort(string &PortInstPort) {
    auto pos = PortInstPort.find(":");
    PortInstNameUnMap[PortInstPort.substr(0, pos)] = PortInstPort.substr(pos + 1);
}

void VerilogStudio::Module::AddParameterOutSideMap(string &ParameterOutSideParameter) {
    auto pos = ParameterOutSideParameter.find(":");
    ParameterOutSideMap[ParameterOutSideParameter.substr(0, pos)] = ParameterOutSideParameter.substr(pos + 1);
}


void VerilogStudio::Module::ShowInstNameUnMap() {
    for (auto &itr: PortInstNameUnMap) {
        cout << itr.first << ":" << itr.second << endl;
    }
}

void VerilogStudio::Module::AddPortDeclaration(string &PortDec) {
    PortDeclaration.emplace_back(PortDec);
}

void VerilogStudio::Module::AddIncludeModule() {
    for(auto &it: IncludeModuleNameUnMap){
        IncludeModule.emplace(it.first);
    }
}

std::set<std::string> VerilogStudio::Module::GetIncludeModuleName() {
    return IncludeModule;
}

void VerilogStudio::Module::AddModuleName(const string& guid,const string& ModuleName) {
    ModuleNameVec.emplace_back(ModuleName);
    ModuleNameGuid[guid] = ModuleNameVec;
}

std::unordered_multimap<std::string, std::string> VerilogStudio::Module::GetIncludeModuleNameUnMap() {
    return IncludeModuleNameUnMap;
}

std::unordered_map<std::string, std::string> VerilogStudio::Module::GetIncludeModuleNameMap() {
    return IncludeModuleNameMap;
}




