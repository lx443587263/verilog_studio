//
// Created by 狂飙的西红柿 on 2022/8/24.
//

#include "Module.hpp"

void Module::AddPortName(const string &PortName) {
    PortNameVec.emplace_back(PortName);
}

void Module::AddIncludeModuleName(vector<string> &UnInstModuletName, vector<string> &InstModuletName) {
    for (auto i = 0; i < UnInstModuletName.size(); ++i) {
        ParameterValueUnMap[UnInstModuletName[i]] = InstModuletName[i];
    }
}

void Module::AddParameter(vector<string> &ParameterName, vector<string> &ParameterValue) {
    for (auto i = 0; i < ParameterName.size(); ++i) {
        ParameterValueUnMap[ParameterName[i]] = ParameterValue[i];
    }
}

void Module::AddInstPort(string &PortInstPort) {
    auto pos = PortInstPort.find(":");
    PortInstNameUnMap[PortInstPort.substr(0,pos)] = PortInstPort.substr(pos+1);
}


void Module::ShowInstNameUnMap() {
    for(auto& itr:PortInstNameUnMap){
        cout<<itr.first<<":"<<itr.second<<endl;
    }
}
