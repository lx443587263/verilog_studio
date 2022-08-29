//
// Created by 狂飙的西红柿 on 2022/8/19.
//

/************************************************
 *******************header***********************
 ************************************************/
#include "Parse.hpp"

/**********************************************/
void VerilogStudio::Parse::ReadJson(string &JsonFile) {
    ifstream in(JsonFile.data());
    if (!in.is_open())
        cerr << "err here:" << __FILE__ << __LINE__ << endl;

    string json_content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    doc.Parse(json_content.c_str());

}

/**********************************************/
unsigned int VerilogStudio::Parse::random_char() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
}

/**********************************************/
std::string VerilogStudio::Parse::generate_hex(const unsigned int len) {
    std::stringstream ss;
    for (auto i = 0; i < len; i++) {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? "0" + hex : hex);
    }
    return ss.str();
}

/**********************************************/
void VerilogStudio::Parse::ParseVerilog(string &FileName) {
    string FileGuid = generate_hex(15);
    FileNameGuid[FileGuid] = FileName;
    if (doc.HasMember(FileName.c_str())) {
        for (auto itr = doc[FileName.c_str()].MemberBegin(); itr != doc[FileName.c_str()].MemberEnd(); ++itr) {
            if (itr->name == "tree" && itr->value.IsObject()) {
                for (auto itr1 = itr->value.MemberBegin(); itr1 != itr->value.MemberEnd(); itr1++) {
                    if (itr1->value == "kDescriptionList") {
                        if ((itr1 - 1)->value.IsArray()) {
                            for (auto itr2 = (itr1 - 1)->value.Begin(); itr2 != (itr1 - 1)->value.End(); ++itr2) {
                                if (itr2->IsObject()) {
                                    for (auto itr3 = itr2->GetObject().MemberBegin(); itr3 != itr2->GetObject().MemberEnd(); ++itr3) {
                                        if (itr3->value.IsString() && itr3->value == "kModuleDeclaration") {
                                            if ((itr3 - 1)->value.IsArray()) {
                                                for (auto itr4 = (itr3 - 1)->value.Begin(); itr4 != (itr3 - 1)->value.End(); ++itr4) {
                                                    if (itr4->IsObject()) {
                                                        for (auto itr5 = itr4->GetObject().MemberBegin(); itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                            if (itr5->value == "kModuleHeader") {
                                                                GetModuleName(itr5);
                                                            } else if (itr5->value == "kModuleItemList" && (itr5 - 1)->value.IsArray()) {
                                                                for (auto kModuleItemList = (itr5 - 1)->value.Begin(); kModuleItemList != (itr5 - 1)->value.End(); ++kModuleItemList) {
                                                                    if (kModuleItemList->IsObject()) {
                                                                        for (auto ModuleItem = kModuleItemList->GetObject().MemberBegin(); ModuleItem != kModuleItemList->GetObject().MemberEnd(); ++ModuleItem) {
                                                                            if (ModuleItem->value.IsString() && ModuleItem->value == "kModulePortDeclaration" && (ModuleItem - 1)->value.IsArray()) {
                                                                                for (auto MPDec = (ModuleItem - 1)->value.Begin(); MPDec != (ModuleItem - 1)->value.End(); ++MPDec) {
                                                                                    if (MPDec->IsObject()) {
                                                                                        for (auto Dimensions = MPDec->GetObject().MemberBegin(); Dimensions != MPDec->GetObject().MemberEnd(); ++Dimensions) {
                                                                                            if (Dimensions->value == "input") {
                                                                                                //cout << "input" << endl;
                                                                                                tempPortDec += "input:";
                                                                                            } else if (Dimensions->value == "output") {
                                                                                                //cout << "output" << endl;
                                                                                                tempPortDec += "output:";
                                                                                            } else if (Dimensions->value == "inout") {
                                                                                                //cout << "inout" << endl;
                                                                                                tempPortDec += "inout:";
                                                                                            } else if (Dimensions->value == "kPackedDimensions" && (Dimensions - 1)->value.IsArray()) {
                                                                                                RepeatBitWidth(Dimensions);
                                                                                            } else if (Dimensions->value == "kIdentifierList") {
                                                                                                if ((Dimensions - 1)->value.IsArray()) {
                                                                                                    for (auto itr = (Dimensions - 1)->value.Begin(); itr != (Dimensions - 1)->value.End(); ++itr) {
                                                                                                        if (itr->IsObject()) {
                                                                                                            for (auto itr2 = itr->GetObject().MemberBegin(); itr2 != itr->GetObject().MemberEnd(); ++itr2) {
                                                                                                                if ((itr2 + 1)->value.IsString() && (itr2 + 1)->value == "kIdentifierUnpackedDimensions") {
                                                                                                                    if (itr2->value.IsArray()) {
                                                                                                                        for (auto itr3 = itr2->value.Begin(); itr3 != itr2->value.End(); ++itr3) {
                                                                                                                            if (itr3->IsObject()) {
                                                                                                                                for (auto itr4 = itr3->GetObject().MemberBegin(); itr4 != itr3->GetObject().MemberEnd(); ++itr4) {
                                                                                                                                    if (itr4->value.IsString() && itr4->value == "kUnqualifiedId" && (itr4 - 1)->value.IsArray()) {
                                                                                                                                        for (auto itr5 = (itr4 - 1)->value.Begin(); itr5 != (itr4 - 1)->value.End(); ++itr5) {
                                                                                                                                            if (itr5->IsObject()) {
                                                                                                                                                for (auto itr6 = itr5->GetObject().MemberBegin(); itr6 != itr5->GetObject().MemberEnd(); ++itr6) {
                                                                                                                                                    if (itr6->value.IsString() && itr6->value == "SymbolIdentifier" && (itr6 + 1)->name == "text") {
                                                                                                                                                        //cout << (itr6 + 1)->value.GetString() << endl;
                                                                                                                                                        tempPortDec += static_cast<string>((itr6 + 1)->value.GetString());
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    } else if (itr4->value.IsString() && itr4->value == "SymbolIdentifier") {
                                                                                                                                        //cout << (itr4 + 1)->value.GetString() << endl;
                                                                                                                                        tempPortDec += ":" +static_cast<string>((itr4 + 1)->value.GetString());
                                                                                                                                        pModule->AddPortDeclaration(tempPortDec);
                                                                                                                                        tempPortDec.clear();
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }

                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            } else if (Dimensions->value == "kIdentifierUnpackedDimensionsList") {
                                                                                                if ((Dimensions - 1)->value.IsArray()) {
                                                                                                    for (auto UnpackedDim = (Dimensions - 1)->value.Begin(); UnpackedDim != (Dimensions - 1)->value.End(); ++UnpackedDim) {
                                                                                                        for (auto portNameObj = UnpackedDim->GetObject().MemberBegin(); portNameObj != UnpackedDim->GetObject().MemberEnd(); ++portNameObj) {
                                                                                                            if (portNameObj->value.IsArray()) {
                                                                                                                for (auto kUnpackedDimensions = portNameObj->value.Begin(); kUnpackedDimensions != portNameObj->value.End(); ++kUnpackedDimensions) {
                                                                                                                    if (kUnpackedDimensions->IsObject()) {
                                                                                                                        for (auto portName = kUnpackedDimensions->GetObject().MemberBegin(); portName != kUnpackedDimensions->GetObject().MemberEnd(); ++portName) {
                                                                                                                            if (portName->value.IsString() && portName->value == "SymbolIdentifier" && (portName + 1)->name == "text") {
                                                                                                                                //cout <<(portName + 1)->value.GetString() << endl;
                                                                                                                                tempPortDec += static_cast<string>((portName + 1)->value.GetString());
                                                                                                                                pModule->AddPortDeclaration(tempPortDec);
                                                                                                                                tempPortDec.clear();
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            } else if (ModuleItem->value == "kNetDeclaration" && (ModuleItem - 1)->value.IsArray()) {
                                                                                if ((ModuleItem - 1)->value.IsArray()) {
                                                                                    for (auto NetDec = (ModuleItem - 1)->value.Begin(); NetDec != (ModuleItem - 1)->value.End(); ++NetDec) {
                                                                                        if (NetDec->IsObject()) {
                                                                                            for (auto itr = NetDec->GetObject().MemberBegin(); itr != NetDec->GetObject().MemberEnd(); ++itr) {
                                                                                                if (itr->value.IsString() && itr->value == "wire") {
                                                                                                    //cout << "wire" << endl;
                                                                                                    tempPortDec += "wire:";
                                                                                                } else if ((itr - 1)->value.IsArray() && itr->value == "kDataTypeImplicitIdDimensions") {
                                                                                                    for (auto itr2 = (itr - 1)->value.Begin(); itr2 != (itr - 1)->value.End(); ++itr2) {
                                                                                                        if (itr2->IsObject()) {
                                                                                                            for (auto itr3 = itr2->GetObject().MemberBegin(); itr3 != itr2->GetObject().MemberEnd(); ++itr3) {
                                                                                                                if (itr3->value.IsArray()) {
                                                                                                                    for (auto itr4 = itr3->value.Begin(); itr4 != itr3->value.End(); ++itr4) {
                                                                                                                        if (itr4->IsObject()) {
                                                                                                                            for (auto itr5 = itr4->GetObject().MemberBegin(); itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                                                                                                if (itr5->value == "kPackedDimensions" && itr5->value.IsString()) {
                                                                                                                                    RepeatBitWidth(itr5);
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                } else if ((itr - 1)->value.IsArray() && itr->value == "kNetVariableDeclarationAssign") {
                                                                                                    for (auto itr2 = (itr - 1)->value.Begin(); itr2 != (itr - 1)->value.End(); ++itr2) {
                                                                                                        if (itr2->IsObject()) {
                                                                                                            for (auto itr3 = itr2->GetObject().MemberBegin(); itr3 != itr2->GetObject().MemberEnd(); ++itr3) {
                                                                                                                if (itr3->value.IsArray() && (itr3 + 1)->value == "kNetVariable") {
                                                                                                                    for (auto itr4 = itr3->value.Begin(); itr4 != itr3->value.End(); ++itr4) {
                                                                                                                        if (itr4->IsObject()) {
                                                                                                                            for (auto itr5 = itr4->GetObject().MemberBegin(); itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                                                                                                if (itr5->value.IsString() && itr5->value == "SymbolIdentifier" && (itr5 + 1)->name == "text") {
                                                                                                                                    //cout << (itr5 + 1)->value.GetString() << endl;
                                                                                                                                    tempPortDec += static_cast<string>((itr5 + 1)->value.GetString());
                                                                                                                                    pModule->AddPortDeclaration(tempPortDec);
                                                                                                                                    tempPortDec.clear();
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            } else if (ModuleItem->value == "kDataDeclaration" && (ModuleItem - 1)->value.IsArray() && (ModuleItem - 1)->value.IsArray()) {
                                                                                if ((ModuleItem - 1)->value.IsArray()) {
                                                                                    for (auto itr = (ModuleItem - 1)->value.Begin();
                                                                                         itr != (ModuleItem - 1)->value.End(); ++itr) {
                                                                                        if (itr->IsObject()) {
                                                                                            for (auto itr1 = itr->GetObject().MemberBegin(); itr1 != itr->GetObject().MemberEnd(); ++itr1) {
                                                                                                if ((itr1 + 1)->value == "kInstantiationBase" && itr1->value.IsArray()) {
                                                                                                    for (auto itr2 = itr1->value.Begin(); itr2 != itr1->value.End(); ++itr2) {
                                                                                                        if (itr2->IsObject()) {
                                                                                                            for (auto itr3 = itr2->GetObject().MemberBegin(); itr3 != itr2->GetObject().MemberEnd(); ++itr3) {
                                                                                                                if (itr3->value.IsArray() && (itr3 + 1)->value == "kInstantiationType") {
                                                                                                                    for (auto itr4 = itr3->value.Begin(); itr4 != itr3->value.End(); ++itr4) {
                                                                                                                        if (itr4->IsObject()) {
                                                                                                                            for (auto itr5 = itr4->GetObject().MemberBegin(); itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                                                                                                if (itr5->value.IsArray() && (itr5 + 1)->value == "kDataType") {
                                                                                                                                    for (auto itr6 = itr5->value.Begin(); itr6 != itr5->value.End(); ++itr6) {
                                                                                                                                        if (itr6->IsObject()) {
                                                                                                                                            for (auto itr7 = itr6->GetObject().MemberBegin(); itr7 != itr6->GetObject().MemberEnd(); ++itr7) {
                                                                                                                                                if ((itr7 - 1)->value.IsArray() && itr7->value == "kDataTypePrimitive") {
                                                                                                                                                    GetRegName(itr7);
                                                                                                                                                } else if ((itr7 - 1)->value.IsArray() && itr7->value == "kPackedDimensions") {
                                                                                                                                                    RepeatBitWidth(itr7);
                                                                                                                                                } else if (itr7->value.IsArray() && (itr7 + 1)->value == "kUnqualifiedId") {
                                                                                                                                                    GetParameterInst(itr7);
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                } else if (itr3->value.IsArray() && (itr3 + 1)->value == "kGateInstanceRegisterVariableList") {
                                                                                                                    for (auto itr4 = itr3->value.Begin(); itr4 != itr3->value.End(); ++itr4) {
                                                                                                                        if (itr4->IsObject()) {
                                                                                                                            for (auto itr5 = itr4->GetObject().MemberBegin(); itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                                                                                                if (itr5->value.IsArray() && (itr5 + 1)->value == "kRegisterVariable") {
                                                                                                                                    for (auto itr6 = itr5->value.Begin(); itr6 != itr5->value.End(); ++itr6) {
                                                                                                                                        if (itr6->IsObject()) {
                                                                                                                                            for (auto itr7 = itr6->GetObject().MemberBegin(); itr7 != itr6->GetObject().MemberEnd(); ++itr7) {
                                                                                                                                                if (itr7->value.IsString() && itr7->value == "SymbolIdentifier" && (itr7 + 1)->name == "text") {
                                                                                                                                                    //cout <<(itr7 + 1)->value.GetString() << endl;
                                                                                                                                                    tempPortDec += static_cast<string>((itr7 + 1)->value.GetString());
                                                                                                                                                    pModule->AddPortDeclaration(tempPortDec);
                                                                                                                                                    tempPortDec.clear();
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                } else if (itr5->value.IsArray() && (itr5 + 1)->value == "kGateInstance") {
                                                                                                                                    GetInstName(itr5);
                                                                                                                                }
                                                                                                                                pModule->AddIncludeModuleName(UnInstModuleName,InstModuleName);
                                                                                                                                pModule->AddIncludeModule();
                                                                                                                                UnInstModuleName.clear();
                                                                                                                                InstModuleName.clear();
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    KVFileModule[FileGuid] = ModuleNames;
}

/**********************************************/
std::string VerilogStudio::Parse::RepeatInstStruct(Value::MemberIterator &RepeatBitItr) {
    for (auto itr14 = RepeatBitItr->value.Begin(); itr14 != RepeatBitItr->value.End(); ++itr14) {
        if (itr14->IsObject()) {
            for (auto itr15 = itr14->GetObject().MemberBegin(); itr15 != itr14->GetObject().MemberEnd(); ++itr15) {
                if (itr15->value.IsArray() && (itr15 + 1)->value == "kExpression") {
                    for (auto itr16 = itr15->value.Begin(); itr16 != itr15->value.End(); ++itr16) {
                        if (itr16->IsObject()) {
                            for (auto itr17 = itr16->GetObject().MemberBegin(); itr17 != itr16->GetObject().MemberEnd(); ++itr17) {
                                if ((itr17 + 1)->value == "kReferenceCallBase" && itr17->value.IsArray()) {
                                    for (auto itr18 = itr17->value.Begin(); itr18 != itr17->value.End(); ++itr18) {
                                        if (itr18->IsObject()) {
                                            for (auto itr19 = itr18->GetObject().MemberBegin(); itr19 != itr18->GetObject().MemberEnd(); ++itr19) {
                                                if ((itr19 + 1)->value.IsString() && (itr19 + 1)->value == "kReference" && itr19->value.IsArray()) {
                                                    for (auto itr20 = itr19->value.Begin(); itr20 != itr19->value.End(); ++itr20) {
                                                        if (itr20->IsObject()) {
                                                            for (auto itr21 = itr20->GetObject().MemberBegin(); itr21 != itr20->GetObject().MemberEnd(); ++itr21) {
                                                                if ((itr21 + 1)->value.IsString() && (itr21 + 1)->value == "kLocalRoot" && itr21->value.IsArray()) {
                                                                    for (auto itr22 = itr21->value.Begin(); itr22 != itr21->value.End(); ++itr22) {
                                                                        if (itr22->IsObject()) {
                                                                            for (auto itr23 = itr22->GetObject().MemberBegin(); itr23 != itr22->GetObject().MemberEnd(); ++itr23) {
                                                                                if ((itr23 + 1)->value.IsString() && itr23->value.IsArray() && (itr23 + 1)->value == "kUnqualifiedId") {
                                                                                    for (auto itr24 = itr23->value.Begin(); itr24 != itr23->value.End(); ++itr24) {
                                                                                        if (itr24->IsObject()) {
                                                                                            for (auto InstName = itr24->GetObject().MemberBegin(); InstName != itr24->GetObject().MemberEnd(); ++InstName) {
                                                                                                if (InstName->value.IsString() && InstName->value == "SymbolIdentifier" && (InstName + 1)->name == "text") {
                                                                                                    // port name
                                                                                                    return (InstName + 1)->value.GetString();
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return std::string();
}

/**********************************************/
void VerilogStudio::Parse::GetModuleName(Value::MemberIterator &ModuleNameItr) {
    // module header
    guid = generate_hex(20);
    shared_ptr<Module> tempPModule(new Module);
    pModule = tempPModule;
    ModuleGuid[guid] = pModule;

    for (auto mHeader = (ModuleNameItr - 1)->value.Begin(); mHeader != (ModuleNameItr - 1)->value.End(); ++mHeader) {
        if (mHeader->IsObject()) {
            for (auto moduleName = mHeader->GetObject().MemberBegin(); moduleName != mHeader->GetObject().MemberEnd(); ++moduleName) {
                if (moduleName->value.IsString() && moduleName->value == "SymbolIdentifier" && (moduleName + 1)->name == "text") {
                    //cout << (moduleName + 1)->value.GetString() << endl;
                    pModule->AddModuleName(guid,(moduleName + 1)->value.GetString());
                    KVModuleGuid[guid] = (moduleName + 1)->value.GetString();
                    ModuleNames.emplace_back((moduleName + 1)->value.GetString());
                } else if (moduleName->value.IsString() && moduleName->value == "kParenGroup") {
                    GetPortName(moduleName);
                } else if ((moduleName + 1)->value.IsString() && (moduleName + 1)->value == "kFormalParameterListDeclaration" && moduleName->value.IsArray()) {
                    GetParameter(moduleName);
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::RepeatStruct(Value::MemberIterator &RepeatItr) {
    for (auto portObject = RepeatItr->value.Begin(); portObject != RepeatItr->value.End(); ++portObject) {
        if (portObject->IsObject()) {
            for (auto kUnqualifiedId = portObject->GetObject().MemberBegin();
                 kUnqualifiedId != portObject->GetObject().MemberEnd(); ++kUnqualifiedId) {
                if (kUnqualifiedId->value.IsArray()) {
                    for (auto portLastObj = kUnqualifiedId->value.Begin();
                         portLastObj != kUnqualifiedId->value.End(); ++portLastObj) {
                        if (portLastObj->IsObject()) {
                            for (auto port = portLastObj->GetObject().MemberBegin();
                                 port != portLastObj->GetObject().MemberEnd(); ++port) {
                                if (port->value.IsString() && port->value == "SymbolIdentifier") {
                                    //port name
                                    pModule->AddPortName((port + 1)->value.GetString());
                                }
                            }
                        }
                    }
                } else if (kUnqualifiedId->value.IsString() && kUnqualifiedId->value == "SymbolIdentifier" &&
                           (kUnqualifiedId + 1)->name == "text") {
                    //port name
                    //cout <<(kUnqualifiedId+1)->value.GetString()<<endl;
                    tempPortDec += static_cast<string>((kUnqualifiedId+1)->value.GetString());
                    pModule->AddPortName((kUnqualifiedId + 1)->value.GetString());
                    pModule->AddPortDeclaration(tempPortDec);
                    tempPortDec.clear();
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetPortName(Value::MemberIterator &PortNameItr) {
    for (auto portDec = (PortNameItr - 1)->value.Begin(); portDec != (PortNameItr - 1)->value.End(); ++portDec) {
        if (portDec->IsObject()) {
            for (auto portDecList = portDec->GetObject().MemberBegin();
                 portDecList != portDec->GetObject().MemberEnd(); ++portDecList) {
                if (portDecList->value == "kPortDeclarationList" && (portDecList - 1)->value.IsArray()) {
                    for (auto kPortList = (portDecList - 1)->value.Begin();
                         kPortList != (portDecList - 1)->value.End(); ++kPortList) {
                        if (kPortList->IsObject()) {
                            for (auto kPort = kPortList->GetObject().MemberBegin();
                                 kPort != kPortList->GetObject().MemberEnd(); ++kPort) {
                                if (kPort->value.IsString() && kPort->value == "kPort" &&
                                    (kPort - 1)->value.IsArray()) {
                                    for (auto kPortReference = (kPort - 1)->value.Begin();
                                         kPortReference != (kPort - 1)->value.End(); ++kPortReference) {
                                        if (kPortReference->IsObject()) {
                                            for (auto portName = kPortReference->GetObject().MemberBegin();
                                                 portName != kPortReference->GetObject().MemberEnd(); ++portName) {
                                                if (portName->value.IsArray()) {
                                                    //get portName
                                                    RepeatStruct(portName);
                                                }
                                            }
                                        }
                                    };
                                } else if (kPort->value.IsString() && kPort->value == "kPortDeclaration" &&
                                           (kPort - 1)->value.IsArray()) {
                                    //get port dec
                                    GetPortDec(kPort);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::RepeatBitWidth(Value::MemberIterator &RepeatItr) {
    for (auto PackedDimensions = (RepeatItr - 1)->value.Begin(); PackedDimensions != (RepeatItr - 1)->value.End(); ++PackedDimensions) {
        if (PackedDimensions->IsObject()) {
            for (auto DecDim = PackedDimensions->GetObject().MemberBegin(); DecDim != PackedDimensions->GetObject().MemberEnd(); ++DecDim) {
                if ((DecDim + 1)->value == "kDeclarationDimensions" && DecDim->value.IsArray()) {
                    for (auto DimRange = DecDim->value.Begin(); DimRange != DecDim->value.End(); ++DimRange) {
                        if (DimRange->IsObject()) {
                            for (auto Exp = DimRange->GetObject().MemberBegin(); Exp != DimRange->GetObject().MemberEnd(); ++Exp) {
                                if (Exp->value.IsArray() && (Exp + 1)->value == "kDimensionRange") {
                                    for (auto dr = Exp->value.Begin(); dr != Exp->value.End(); ++dr) {
                                        if (dr->IsObject()) {
                                            for (auto Expression = dr->GetObject().MemberBegin(); Expression != dr->GetObject().MemberEnd(); ++Expression) {
                                                if ((Expression + 1)->value.IsString() && (Expression + 1)->value == "kExpression") {
                                                    if (Expression->value.IsArray()) {
                                                        for (auto kExp = Expression->value.Begin(); kExp != Expression->value.End(); ++kExp) {
                                                            if (kExp->IsObject()) {
                                                                for (auto kNumber = kExp->GetObject().MemberBegin(); kNumber != kExp->GetObject().MemberEnd(); ++kNumber) {
                                                                    if ((kNumber + 1)->value.IsString() && (kNumber + 1)->value == "kNumber") {
                                                                        for (auto decNum = kNumber->value.Begin(); decNum != kNumber->value.End(); ++decNum) {
                                                                            if (decNum->IsObject()) {
                                                                                for (auto wideNum = decNum->GetObject().MemberBegin(); wideNum != decNum->GetObject().MemberEnd(); ++wideNum) {
                                                                                    if (wideNum->name == "text") {
                                                                                        //cout <<wideNum->value.GetString() << endl;
                                                                                        tempPortDec += static_cast<string>(wideNum->value.GetString())+":";
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetRegName(Value::MemberIterator &RegNameItr) {
    for (auto itr3 = (RegNameItr - 1)->value.Begin(); itr3 != (RegNameItr - 1)->value.End(); ++itr3) {
        if (itr3->IsObject()) {
            for (auto itr4 = itr3->GetObject().MemberBegin(); itr4 != itr3->GetObject().MemberEnd(); ++itr4) {
                if (itr4->value.IsString()) {
                    //reg
                    //cout <<itr4->value.GetString() << endl;
                    //tempPortDec.clear();
                    tempPortDec += static_cast<string>(itr4->value.GetString())+":";
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetPortDec(Value::MemberIterator &PortDecItr) {
    for (auto kPortReference = (PortDecItr - 1)->value.Begin();
         kPortReference != (PortDecItr - 1)->value.End(); ++kPortReference) {
        if (kPortReference->IsObject()) {
            for (auto portName = kPortReference->GetObject().MemberBegin();
                 portName != kPortReference->GetObject().MemberEnd(); ++portName) {
                if (portName->value.IsString() && portName->value == "output" || portName->value == "input" ||
                    portName->value == "inout" || portName->value == "wire" || portName->value == "reg") {
                    //port type
                    //cout<<portName->value.GetString() << endl;
                    tempPortDec += static_cast<string>(portName->value.GetString())+":";
                } else if (portName->value.IsArray()) {
                    RepeatStruct(portName);
                } else if (portName->value.IsString() && portName->value == "kDataType" &&(portName - 1)->value.IsArray()) {
                    for (auto itr = (portName - 1)->value.Begin(); itr != (portName - 1)->value.End(); ++itr) {
                        if (itr->IsObject()) {
                            for (auto itr2 = itr->GetObject().MemberBegin();
                                 itr2 != itr->GetObject().MemberEnd(); ++itr2) {
                                if (itr2->value.IsString() && (itr2 - 1)->value.IsArray() &&
                                    itr2->value == "kDataTypePrimitive") {
                                    //get reg
                                    GetRegName(itr2);
                                } else if (itr2->value.IsString() && (itr2 - 1)->value.IsArray() &&
                                           itr2->value == "kPackedDimensions" && (itr2 - 1)->value.IsArray()) {
                                    //get bit width
                                    RepeatBitWidth(itr2);

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetInstName(Value::MemberIterator &InstNameItr) {
    for (auto itr6 = InstNameItr->value.Begin(); itr6 != InstNameItr->value.End(); ++itr6) {
        if (itr6->IsObject()) {
            for (auto itr7 = itr6->GetObject().MemberBegin(); itr7 != itr6->GetObject().MemberEnd(); ++itr7) {
                if (itr7->value.IsString() && itr7->value == "SymbolIdentifier" && (itr7 + 1)->name == "text") {
                    // inst module name
                    //cout <<(itr7 + 1)->value.GetString() << endl;
                    InstModuleName.emplace_back((itr7 + 1)->value.GetString());
                } else if (itr7->value.IsArray() && (itr7 + 1)->value == "kParenGroup") {
                    GetInstPort(itr7);
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetInstPort(Value::MemberIterator &InstPortItr) {
    string ResStr;
    for (auto itr8 = InstPortItr->value.Begin(); itr8 != InstPortItr->value.End(); ++itr8) {
        if (itr8->IsObject()) {
            for (auto itr9 = itr8->GetObject().MemberBegin(); itr9 != itr8->GetObject().MemberEnd(); ++itr9) {
                if (itr9->value.IsArray() && (itr9 + 1)->value == "kPortActualList") {
                    for (auto itr10 = itr9->value.Begin(); itr10 != itr9->value.End(); ++itr10) {
                        if (itr10->IsObject()) {
                            for (auto itr11 = itr10->GetObject().MemberBegin(); itr11 != itr10->GetObject().MemberEnd(); ++itr11) {
                                if (itr11->value.IsArray() && (itr11 + 1)->value == "kActualNamedPort") {
                                    for (auto itr12 = itr11->value.Begin(); itr12 != itr11->value.End(); ++itr12) {
                                        if (itr12->IsObject()) {
                                            for (auto itr13 = itr12->GetObject().MemberBegin(); itr13 != itr12->GetObject().MemberEnd(); ++itr13) {
                                                if (itr13->value.IsString() && itr13->value == ".") {
                                                    //cout << itr13->value.GetString();
                                                    ResStr = static_cast<string>(itr13->value.GetString());
                                                } else if (itr13->value.IsString() && itr13->value == "SymbolIdentifier" && (itr13 + 1)->name == "text") {
                                                    //port name
                                                    //cout <<(itr13 + 1)->value.GetString() << endl;
                                                    ResStr += static_cast<string>((itr13 + 1)->value.GetString());
                                                } else if (itr13->value.IsArray() && (itr13 + 1)->value == "kParenGroup") {
                                                    // inst port name
                                                    ResStr = ResStr + ":" +RepeatInstStruct(itr13);
                                                }
                                            }
                                        }
                                    }
                                    pModule->AddInstPort(ResStr);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**********************************************/
void VerilogStudio::Parse::GetParameter(Value::MemberIterator &ParameterItr) {
    vector<string> tempParameterName,tempParameterValue;
    for (auto itr = ParameterItr->value.Begin(); itr != ParameterItr->value.End(); ++itr) {
        if (itr->IsObject()) {
            for (auto itr2 = itr->GetObject().MemberBegin(); itr2 != itr->GetObject().MemberEnd(); ++itr2) {
                if ((itr2 + 1)->value == "kParenGroup" && (itr2 + 1)->value.IsString() && itr2->value.IsArray()) {
                    for (auto itr3 = itr2->value.Begin(); itr3 != itr2->value.End(); ++itr3) {
                        if (itr3->IsObject()) {
                            for (auto itr4 = itr3->GetObject().MemberBegin(); itr4 != itr3->GetObject().MemberEnd(); ++itr4) {
                                if ((itr4 + 1)->value.IsString() && (itr4 + 1)->value == "kFormalParameterList" && itr4->value.IsArray()) {
                                    for (auto itr5 = itr4->value.Begin(); itr5 != itr4->value.End(); ++itr5) {
                                        if (itr5->IsObject()) {
                                            for (auto itr6 = itr5->GetObject().MemberBegin(); itr6 != itr5->GetObject().MemberEnd(); ++itr6) {
                                                if ((itr6 + 1)->value == "kParamDeclaration" && (itr6 + 1)->value.IsString() && itr6->value.IsArray()) {
                                                    for (auto itr7 = itr6->value.Begin(); itr7 != itr6->value.End(); ++itr7) {
                                                        if (itr7->IsObject()) {
                                                            for (auto itr8 = itr7->GetObject().MemberBegin(); itr8 != itr7->GetObject().MemberEnd(); ++itr8) {
                                                                if ((itr8 + 1)->value.IsString() && (itr8 + 1)->value == "kParamType" && itr8->value.IsArray()) {
                                                                    for (auto itr9 = itr8->value.Begin(); itr9 != itr8->value.End(); ++itr9) {
                                                                        if (itr9->IsObject()) {
                                                                            for (auto itr10 = itr9->GetObject().MemberBegin(); itr10 != itr9->GetObject().MemberEnd(); ++itr10) {
                                                                                if ((itr10 + 1)->value == "kUnqualifiedId" && (itr10 + 1)->value.IsString() && itr10->value.IsArray()) {
                                                                                    for (auto itr11 = itr10->value.Begin(); itr11 != itr10->value.End(); ++itr11) {
                                                                                        if (itr11->IsObject()) {
                                                                                            for (auto itr12 = itr11->GetObject().MemberBegin(); itr12 != itr11->GetObject().MemberEnd(); ++itr12) {
                                                                                                if (itr12->value.IsString() && itr12->value == "SymbolIdentifier" && (itr12 + 1)->name == "text") {
                                                                                                    //cout << (itr12 + 1)->value.GetString()<<" ";
                                                                                                    tempParameterName.emplace_back((itr12 + 1)->value.GetString());
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                } else if ((itr8 + 1)->value.IsString() && (itr8 + 1)->value == "kTrailingAssign" && itr8->value.IsArray()) {
                                                                    for (auto dr = itr8->value.Begin(); dr != itr8->value.End(); ++dr) {
                                                                        if (dr->IsObject()) {
                                                                            for (auto Expression = dr->GetObject().MemberBegin(); Expression != dr->GetObject().MemberEnd(); ++Expression) {
                                                                                if ((Expression + 1)->value.IsString() && (Expression + 1)->value == "kExpression") {
                                                                                    if (Expression->value.IsArray()) {
                                                                                        for (auto kExp = Expression->value.Begin(); kExp != Expression->value.End(); ++kExp) {
                                                                                            if (kExp->IsObject()) {
                                                                                                for (auto kNumber = kExp->GetObject().MemberBegin(); kNumber != kExp->GetObject().MemberEnd(); ++kNumber) {
                                                                                                    if ((kNumber + 1)->value.IsString() && (kNumber + 1)->value == "kNumber") {
                                                                                                        for (auto decNum = kNumber->value.Begin(); decNum != kNumber->value.End(); ++decNum) {
                                                                                                            if (decNum->IsObject()) {
                                                                                                                for (auto wideNum = decNum->GetObject().MemberBegin(); wideNum != decNum->GetObject().MemberEnd(); ++wideNum) {
                                                                                                                    if (wideNum->name == "text") {
                                                                                                                        //cout << wideNum->value.GetString() << endl;
                                                                                                                        tempParameterValue.emplace_back(wideNum->value.GetString());
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    pModule->AddParameter(tempParameterName,tempParameterValue);
}

/**********************************************/
void VerilogStudio::Parse::GetParameterInst(Value::MemberIterator &ParameterItr) {
    string ResStr;
    for (auto itr8 = ParameterItr->value.Begin(); itr8 != ParameterItr->value.End(); ++itr8) {
        if (itr8->IsObject()) {
            for (auto itr9 = itr8->GetObject().MemberBegin(); itr9 != itr8->GetObject().MemberEnd(); ++itr9) {
                //get inst
                if (itr9->value.IsString() && itr9->value == "SymbolIdentifier" && (itr9 + 1)->name == "text") {
                    //module old name
                    //cout << "09090" << (itr9 + 1)->value.GetString() << endl;
                    UnInstModuleName.emplace_back((itr9 + 1)->value.GetString());
                } else if (itr9->value.IsString() && itr9->value == "kActualParameterList" && (itr9 - 1)->value.IsArray()) {
                    for (auto itr10 = (itr9 - 1)->value.Begin(); itr10 != (itr9 - 1)->value.End(); ++itr10) {
                        if (itr10->IsObject()) {
                            for (auto itr11 = itr10->GetObject().MemberBegin(); itr11 != itr10->GetObject().MemberEnd(); ++itr11) {
                                if ((itr11 + 1)->value == "kParenGroup" && itr11->value.IsArray()) {
                                    for (auto itr12 = itr11->value.Begin(); itr12 != itr11->value.End(); ++itr12) {
                                        if (itr12->IsObject()) {
                                            for (auto itr13 = itr12->GetObject().MemberBegin(); itr13 != itr12->GetObject().MemberEnd(); ++itr13) {
                                                if (itr13->value.IsArray() && (itr13 + 1)->value == "kActualParameterByNameList") {
                                                    for (auto itr14 = itr13->value.Begin(); itr14 != itr13->value.End(); ++itr14) {
                                                        if (itr14->IsObject()) {
                                                            for (auto itr15 = itr14->GetObject().MemberBegin(); itr15 != itr14->GetObject().MemberEnd(); ++itr15) {
                                                                if (itr15->value.IsArray() && (itr15 + 1)->value == "kParamByName") {
                                                                    for (auto itr16 = itr15->value.Begin(); itr16 != itr15->value.End(); ++itr16) {
                                                                        if (itr16->IsObject()) {
                                                                            for (auto itr17 = itr16->GetObject().MemberBegin(); itr17 != itr16->GetObject().MemberEnd(); ++itr17) {
                                                                                //get outside parameter
                                                                                if (itr17->value.IsString() && itr17->value == ".") {
                                                                                    //cout << itr17->value.GetString();
                                                                                    ResStr = static_cast<string>(itr17->value.GetString());
                                                                                } else if (itr17->value.IsString() && itr17->value == "SymbolIdentifier" && (itr17 + 1)->name == "text") {
                                                                                    //cout  << "***" <<(itr17 + 1)->value.GetString() << endl;
                                                                                    ResStr += static_cast<string>((itr17 + 1)->value.GetString());
                                                                                } else if ((itr17 + 1)->value.IsString() && (itr17 + 1)->value == "kParenGroup" && itr17->value.IsArray()) {
                                                                                    //cout<< "9090" << RepeatInstStruct(itr17) <<endl;
                                                                                    ResStr += ":"+RepeatInstStruct(itr17);
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                    pModule->AddParameterOutSideMap(ResStr);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

std::set<std::string> VerilogStudio::Parse::GetModuleNameGuid(std::string &ModuleName) {
    set<string> temp;
    auto it = find_if(KVModuleGuid.begin(), KVModuleGuid.end(), finder(ModuleName));
    if(it!=KVModuleGuid.end()){
        temp = GetIncludeModuleSet((*it).first);
    }

//    for(auto& it:KVModuleGuid){
//        if(it.second == ModuleName){
//            GetIncludeModuleSet(it.first);
//        }
//    }

    return temp;
}

std::set<std::string> VerilogStudio::Parse::GetIncludeModuleSet(const std::string &guid) {
    set<string> temp;

    auto search = ModuleGuid.find(guid);
    if(search!=ModuleGuid.end()){
        temp = search->second->GetIncludeModuleName();
    }

//    for(auto &it:ModuleGuid){
//        if(it.first == guid){
//            temp = it.second->GetIncludeModuleName();
//        }
//    }

    return temp;
}




