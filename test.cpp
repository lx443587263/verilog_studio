#include <iostream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>


using namespace std;
using namespace rapidjson;

constexpr int MAXBUFFER = 65536;




int main(int argc,char* argv[]) {
//    FILE *fp = fopen("/Users/liuxi/CLionProjects/verilog_studio/c.json", "r");
//    char readBuffer[MAXBUFFER];
//    FileReadStream is(fp, readBuffer, MAXBUFFER);

    string filename = "/Users/liuxi/CLionProjects/verilog_studio/c.json";
    ifstream in(filename.data());
    if(!in.is_open()){
        printf("err here:%s,%d\r\n",__FILE__,__LINE__);
        printf("faild open %s\r\n",filename.data());
    }
    string json_content((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
    in.close();

    Document doc;
    //doc.ParseStream(is);
    doc.Parse(json_content.c_str());


    if (doc.HasMember("test01.v")) {
        for (auto itr = doc["test01.v"].MemberBegin(); itr != doc["test01.v"].MemberEnd(); ++itr) {
            if (itr->name == "tree" && itr->value.IsObject()) {
                for (auto itr1 = itr->value.MemberBegin(); itr1 != itr->value.MemberEnd(); itr1++) {
                    if (itr1->value == "kDescriptionList") {
                        if ((itr1 - 1)->value.IsArray()) {
                            for (auto itr2 = (itr1 - 1)->value.Begin(); itr2 != (itr1 - 1)->value.End(); ++itr2) {
                                if (itr2->IsObject()) {
                                    for (auto itr3 = itr2->GetObject().MemberBegin();
                                         itr3 != itr2->GetObject().MemberEnd(); ++itr3) {
                                        if (itr3->value.IsString() && itr3->value == "kModuleDeclaration") {
                                            if ((itr3 - 1)->value.IsArray()) {
                                                for (auto itr4 = (itr3 - 1)->value.Begin();
                                                     itr4 != (itr3 - 1)->value.End(); ++itr4) {
                                                    if (itr4->IsObject()) {
                                                        for (auto itr5 = itr4->GetObject().MemberBegin();
                                                             itr5 != itr4->GetObject().MemberEnd(); ++itr5) {
                                                            if (itr5->value == "kModuleHeader") {
                                                                if ((itr5 - 1)->value.IsArray()) {
                                                                    // module header
                                                                    for (auto mHeader = (itr5 - 1)->value.Begin();
                                                                         mHeader !=
                                                                         (itr5 - 1)->value.End(); ++mHeader) {
                                                                        if (mHeader->IsObject()) {
                                                                            for (auto moduleName = mHeader->GetObject().MemberBegin();
                                                                                 moduleName !=
                                                                                 mHeader->GetObject().MemberEnd(); ++moduleName) {
                                                                                if (moduleName->value.IsString() &&
                                                                                    moduleName->value ==
                                                                                    "SymbolIdentifier") {
                                                                                    //cout<< "module name:"<<(moduleName+1)->value.GetString()<< endl;
                                                                                    //repair
                                                                                }
                                                                                else if(moduleName->value.IsString() && moduleName->value == "kParenGroup"){
                                                                                    for(auto portDec = (moduleName-1)->value.Begin();portDec != (moduleName-1)->value.End();++portDec){
                                                                                        if(portDec->IsObject()){
                                                                                            //cout<<"is object"<<endl;
                                                                                            for(auto portDecList = portDec->GetObject().MemberBegin();portDecList!=portDec->GetObject().MemberEnd();++portDecList){
                                                                                                if(portDecList->value == "kPortDeclarationList" && (portDecList-1)->value.IsArray()){
                                                                                                    for(auto kPortList = (portDecList-1)->value.Begin();kPortList!=(portDecList-1)->value.End();++kPortList){
                                                                                                        if(kPortList->IsObject()){
                                                                                                            for(auto kPort = kPortList->GetObject().MemberBegin();kPort!=kPortList->GetObject().MemberEnd();++kPort){
                                                                                                                if(kPort->value.IsString()&&kPort->value == "kPort"){
                                                                                                                    if((kPort-1)->value.IsArray()){
                                                                                                                        //repair
                                                                                                                        for(auto kPortReference = (kPort-1)->value.Begin();kPortReference!=(kPort-1)->value.End();++kPortReference){
                                                                                                                            if(kPortReference->IsObject()){
                                                                                                                                for(auto portName = kPortReference->GetObject().MemberBegin();portName != kPortReference->GetObject().MemberEnd();++portName){
                                                                                                                                    if(portName->value.IsArray()){
                                                                                                                                        for(auto portObject = portName->value.Begin();portObject!=portName->value.End();++portObject){
                                                                                                                                            if(portObject->IsObject()){
                                                                                                                                                //repair
                                                                                                                                                for(auto kUnqualifiedId = portObject->GetObject().MemberBegin();kUnqualifiedId != portObject->GetObject().MemberEnd();++kUnqualifiedId){
                                                                                                                                                    if(kUnqualifiedId->value.IsArray()){
                                                                                                                                                        for(auto portLastObj = kUnqualifiedId->value.Begin();portLastObj!=kUnqualifiedId->value.End();++portLastObj){
                                                                                                                                                            if(portLastObj->IsObject()){
                                                                                                                                                                for(auto port = portLastObj->GetObject().MemberBegin();port != portLastObj->GetObject().MemberEnd();++port){
                                                                                                                                                                    if(port->value.IsString() && port->value == "SymbolIdentifier"){
                                                                                                                                                                        cout << "prot name:"<<(port+1)->value.GetString()<<endl;
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
                                                                                                                else if(kPort->value.IsString()&&kPort->value == "kPortDeclaration" && (kPort-1)->value.IsArray()){
                                                                                                                    for(auto kPortReference = (kPort-1)->value.Begin();kPortReference!=(kPort-1)->value.End();++kPortReference) {
                                                                                                                        if(kPortReference->IsObject()){
                                                                                                                            for(auto portName = kPortReference->GetObject().MemberBegin();portName != kPortReference->GetObject().MemberEnd();++portName) {
                                                                                                                                if(portName->value.IsString()&& portName->value == "output"||portName->value =="input"||portName->value =="inout"||portName->value =="wire"||portName->value =="reg"){
                                                                                                                                    //cout<<portName->value.GetString()<<endl;
                                                                                                                                }else if(portName->value.IsArray()){
                                                                                                                                    for(auto portObject = portName->value.Begin();portObject!=portName->value.End();++portObject){
                                                                                                                                        if(portObject->IsObject()){
                                                                                                                                            //repair
                                                                                                                                            for(auto kUnqualifiedId = portObject->GetObject().MemberBegin();kUnqualifiedId != portObject->GetObject().MemberEnd();++kUnqualifiedId){
                                                                                                                                                if(kUnqualifiedId->value.IsArray()){
                                                                                                                                                    for(auto portLastObj = kUnqualifiedId->value.Begin();portLastObj!=kUnqualifiedId->value.End();++portLastObj){
                                                                                                                                                        if(portLastObj->IsObject()){
                                                                                                                                                            for(auto port = portLastObj->GetObject().MemberBegin();port != portLastObj->GetObject().MemberEnd();++port){
                                                                                                                                                                if(port->value.IsString() && port->value == "SymbolIdentifier"){
                                                                                                                                                                    cout << "prot name:"<<(port+1)->value.GetString()<<endl;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                } else if(kUnqualifiedId->value.IsString() && kUnqualifiedId->value=="SymbolIdentifier" && (kUnqualifiedId+1)->name == "text"){
                                                                                                                                                    //port name
                                                                                                                                                    cout << (kUnqualifiedId+1)->value.GetString()<<endl;
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }else if(portName->value.IsString()&&portName->value == "kDataType"&&(portName-1)->value.IsArray()){
                                                                                                                                    for(auto itr = (portName-1)->value.Begin();itr != (portName-1)->value.End();++itr){
                                                                                                                                        if(itr->IsObject()){
                                                                                                                                            for(auto itr2 = itr->GetObject().MemberBegin();itr2 != itr->GetObject().MemberEnd();++itr2){
                                                                                                                                                if(itr2->value.IsString()&&(itr2-1)->value.IsArray()&&itr2->value == "kDataTypePrimitive"){
                                                                                                                                                    for(auto itr3=(itr2-1)->value.Begin();itr3!=(itr2-1)->value.End();++itr3){
                                                                                                                                                        if(itr3->IsObject()){
                                                                                                                                                            for(auto itr4 = itr3->GetObject().MemberBegin(); itr4 != itr3->GetObject().MemberEnd();++itr4){
                                                                                                                                                                if(itr4->value.IsString()){
                                                                                                                                                                    //reg
                                                                                                                                                                    cout <<itr4->value.GetString()<<endl;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }else if(itr2->value.IsString()&&(itr2-1)->value.IsArray()&&itr2->value == "kPackedDimensions"){
                                                                                                                                                    //repair
                                                                                                                                                    if((itr2-1)->value.IsArray()){
                                                                                                                                                        for(auto PackedDimensions = (itr2-1)->value.Begin();PackedDimensions != (itr2-1)->value.End();++PackedDimensions){
                                                                                                                                                            if(PackedDimensions->IsObject()){
                                                                                                                                                                for(auto DecDim = PackedDimensions->GetObject().MemberBegin();DecDim != PackedDimensions->GetObject().MemberEnd();++DecDim ){
                                                                                                                                                                    if((DecDim+1)->value=="kDeclarationDimensions"&&DecDim->value.IsArray()){
                                                                                                                                                                        for(auto DimRange = DecDim->value.Begin();DimRange != DecDim->value.End();++DimRange){
                                                                                                                                                                            if(DimRange->IsObject()){
                                                                                                                                                                                for(auto Exp = DimRange->GetObject().MemberBegin();Exp != DimRange->GetObject().MemberEnd();++Exp){
                                                                                                                                                                                    if(Exp->value.IsArray() && (Exp+1)->value=="kDimensionRange"){
                                                                                                                                                                                        for(auto dr = Exp->value.Begin();dr != Exp->value.End();++dr){
                                                                                                                                                                                            if(dr->IsObject()){
                                                                                                                                                                                                for(auto Expression = dr->GetObject().MemberBegin();Expression != dr->GetObject().MemberEnd();++Expression){
                                                                                                                                                                                                    if((Expression+1)->value.IsString()&&(Expression+1)->value=="kExpression"){
                                                                                                                                                                                                        if(Expression->value.IsArray()){
                                                                                                                                                                                                            for(auto kExp = Expression->value.Begin(); kExp != Expression->value.End();++kExp){
                                                                                                                                                                                                                if(kExp->IsObject()){
                                                                                                                                                                                                                    for(auto kNumber = kExp->GetObject().MemberBegin();kNumber != kExp->GetObject().MemberEnd();++kNumber){
                                                                                                                                                                                                                        if((kNumber+1)->value.IsString() && (kNumber+1)->value=="kNumber"){
                                                                                                                                                                                                                            for(auto decNum = kNumber->value.Begin();decNum != kNumber->value.End();++decNum){
                                                                                                                                                                                                                                if(decNum->IsObject()){
                                                                                                                                                                                                                                    for(auto wideNum = decNum->GetObject().MemberBegin();wideNum != decNum->GetObject().MemberEnd();++wideNum){
                                                                                                                                                                                                                                        if(wideNum->name=="text"){
                                                                                                                                                                                                                                            cout <<wideNum->value.GetString()<<endl;
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
                                                            else if (itr5->value == "kModuleItemList"&&(itr5-1)->value.IsArray()) {
                                                                for(auto kModuleItemList = (itr5-1)->value.Begin();kModuleItemList != (itr5-1)->value.End();++kModuleItemList){
                                                                    if(kModuleItemList->IsObject()){
                                                                        for(auto ModuleItem = kModuleItemList->GetObject().MemberBegin();ModuleItem != kModuleItemList->GetObject().MemberEnd();++ModuleItem){
                                                                            if(ModuleItem->value.IsString()){
                                                                                if(ModuleItem->value == "kModulePortDeclaration"){
                                                                                    if((ModuleItem-1)->value.IsArray()){
                                                                                        for(auto MPDec = (ModuleItem-1)->value.Begin();MPDec != (ModuleItem-1)->value.End();++MPDec){
                                                                                            if(MPDec->IsObject()){
                                                                                                for(auto Dimensions = MPDec->GetObject().MemberBegin();Dimensions!= MPDec->GetObject().MemberEnd();++Dimensions){
                                                                                                    if(Dimensions->value=="input"){
                                                                                                        cout<<"input"<<endl;
                                                                                                    }else if(Dimensions->value=="output"){
                                                                                                        cout<<"output"<<endl;
                                                                                                    }else if(Dimensions->value=="inout"){
                                                                                                        cout<<"inout"<<endl;
                                                                                                    }else if(Dimensions->value=="kPackedDimensions"){
                                                                                                        //rapair
                                                                                                        if((Dimensions-1)->value.IsArray()){
                                                                                                            for(auto PackedDimensions = (Dimensions-1)->value.Begin();PackedDimensions != (Dimensions-1)->value.End();++PackedDimensions){
                                                                                                                if(PackedDimensions->IsObject()){
                                                                                                                    for(auto DecDim = PackedDimensions->GetObject().MemberBegin();DecDim != PackedDimensions->GetObject().MemberEnd();++DecDim ){
                                                                                                                        if((DecDim+1)->value=="kDeclarationDimensions"&&DecDim->value.IsArray()){
                                                                                                                            for(auto DimRange = DecDim->value.Begin();DimRange != DecDim->value.End();++DimRange){
                                                                                                                                if(DimRange->IsObject()){
                                                                                                                                    for(auto Exp = DimRange->GetObject().MemberBegin();Exp != DimRange->GetObject().MemberEnd();++Exp){
                                                                                                                                        if(Exp->value.IsArray() && (Exp+1)->value=="kDimensionRange"){
                                                                                                                                            for(auto dr = Exp->value.Begin();dr != Exp->value.End();++dr){
                                                                                                                                                if(dr->IsObject()){
                                                                                                                                                    for(auto Expression = dr->GetObject().MemberBegin();Expression != dr->GetObject().MemberEnd();++Expression){
                                                                                                                                                        if((Expression+1)->value.IsString()&&(Expression+1)->value=="kExpression"){
                                                                                                                                                            if(Expression->value.IsArray()){
                                                                                                                                                                for(auto kExp = Expression->value.Begin(); kExp != Expression->value.End();++kExp){
                                                                                                                                                                    if(kExp->IsObject()){
                                                                                                                                                                        for(auto kNumber = kExp->GetObject().MemberBegin();kNumber != kExp->GetObject().MemberEnd();++kNumber){
                                                                                                                                                                            if((kNumber+1)->value.IsString() && (kNumber+1)->value=="kNumber"){
                                                                                                                                                                                for(auto decNum = kNumber->value.Begin();decNum != kNumber->value.End();++decNum){
                                                                                                                                                                                    if(decNum->IsObject()){
                                                                                                                                                                                        for(auto wideNum = decNum->GetObject().MemberBegin();wideNum != decNum->GetObject().MemberEnd();++wideNum){
                                                                                                                                                                                            if(wideNum->name=="text"){
                                                                                                                                                                                                cout <<wideNum->value.GetString()<<endl;
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
                                                                                                    }else if(Dimensions->value=="kIdentifierList"){
                                                                                                        if((Dimensions-1)->value.IsArray()){
                                                                                                            for(auto itr = (Dimensions-1)->value.Begin();itr!= (Dimensions-1)->value.End();++itr){
                                                                                                                if(itr->IsObject()){
                                                                                                                    for(auto itr2 = itr->GetObject().MemberBegin();itr2 != itr->GetObject().MemberEnd();++itr2){
                                                                                                                        if((itr2+1)->value.IsString() && (itr2+1)->value=="kIdentifierUnpackedDimensions"){
                                                                                                                            if(itr2->value.IsArray()){
                                                                                                                                for(auto itr3 = itr2->value.Begin();itr3!= itr2->value.End();++itr3){
                                                                                                                                    if(itr3->IsObject()){
                                                                                                                                        for(auto itr4= itr3->GetObject().MemberBegin();itr4!= itr3->GetObject().MemberEnd();++itr4){
                                                                                                                                            if(itr4->value.IsString()&&itr4->value=="kUnqualifiedId"&&(itr4-1)->value.IsArray()){
                                                                                                                                                for(auto itr5 = (itr4-1)->value.Begin();itr5 != (itr4-1)->value.End();++itr5){
                                                                                                                                                    if(itr5->IsObject()){
                                                                                                                                                        for(auto itr6 = itr5->GetObject().MemberBegin();itr6 != itr5->GetObject().MemberEnd();++itr6){
                                                                                                                                                            if(itr6->value.IsString()&&itr6->value=="SymbolIdentifier"&&(itr6+1)->name=="text"){
                                                                                                                                                                cout<<(itr6+1)->value.GetString()<<endl;
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            if(itr4->value.IsString() && itr4->value=="SymbolIdentifier"){
                                                                                                                                                cout << (itr4+1)->value.GetString()<<endl;
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
                                                                                                    }else if(Dimensions->value=="kIdentifierUnpackedDimensionsList"){
                                                                                                        if((Dimensions-1)->value.IsArray()){
                                                                                                            for(auto UnpackedDim = (Dimensions-1)->value.Begin();UnpackedDim !=(Dimensions-1)->value.End();++UnpackedDim){
                                                                                                                for(auto portNameObj = UnpackedDim->GetObject().MemberBegin();portNameObj != UnpackedDim->GetObject().MemberEnd();++portNameObj){
                                                                                                                    if(portNameObj->value.IsArray()){
                                                                                                                        for(auto kUnpackedDimensions = portNameObj->value.Begin();kUnpackedDimensions != portNameObj->value.End();++kUnpackedDimensions){
                                                                                                                            if(kUnpackedDimensions->IsObject()){
                                                                                                                                for(auto portName = kUnpackedDimensions->GetObject().MemberBegin();portName != kUnpackedDimensions->GetObject().MemberEnd();++portName){
                                                                                                                                    if(portName->value.IsString()&&portName->value=="SymbolIdentifier"&&(portName+1)->name=="text"){
                                                                                                                                        cout << (portName+1)->value.GetString()<<endl;
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
                                                                                else if(ModuleItem->value == "kNetDeclaration"){
                                                                                    if((ModuleItem-1)->value.IsArray()){
                                                                                        for(auto NetDec = (ModuleItem-1)->value.Begin();NetDec != (ModuleItem-1)->value.End();++NetDec){
                                                                                            if(NetDec->IsObject()){
                                                                                                for(auto itr = NetDec->GetObject().MemberBegin();itr != NetDec->GetObject().MemberEnd();++itr){
                                                                                                    if(itr->value.IsString()&&itr->value=="wire"){
                                                                                                        cout << "wire"<<endl;
                                                                                                    }else if((itr-1)->value.IsArray()&&itr->value=="kDataTypeImplicitIdDimensions"){
                                                                                                        for(auto itr2 = (itr-1)->value.Begin(); itr2 != (itr-1)->value.End();++itr2){
                                                                                                            if(itr2->IsObject()){
                                                                                                                for(auto itr3 = itr2->GetObject().MemberBegin();itr3 != itr2->GetObject().MemberEnd();++itr3){
                                                                                                                    if(itr3->value.IsArray()){
                                                                                                                        for(auto itr4 = itr3->value.Begin();itr4 != itr3->value.End();++itr4){
                                                                                                                            if(itr4->IsObject()){
                                                                                                                                for(auto itr5 = itr4->GetObject().MemberBegin();itr5 != itr4->GetObject().MemberEnd();++itr5){
                                                                                                                                    if(itr5->value=="kPackedDimensions"&&itr5->value.IsString()){
                                                                                                                                        //repair
                                                                                                                                        for(auto itr6=(itr5-1)->value.Begin();itr6!=(itr5-1)->value.End();++itr6){
                                                                                                                                            if(itr6->IsObject()){
                                                                                                                                                for(auto itr7= itr6->GetObject().MemberBegin();itr7 != itr6->GetObject().MemberEnd();++itr7){
                                                                                                                                                    if(itr7->value.IsArray()&&(itr7+1)->value=="kDeclarationDimensions"){
                                                                                                                                                        for(auto itr8 = itr7->value.Begin();itr8 != itr7->value.End();++itr8){
                                                                                                                                                            if(itr8->IsObject()){
                                                                                                                                                                for(auto itr9 =itr8->GetObject().MemberBegin();itr9 !=itr8->GetObject().MemberEnd();++itr9){
                                                                                                                                                                    //repair
                                                                                                                                                                    if( itr9->value.IsArray()&&(itr9+1)->value=="kDimensionRange"){
                                                                                                                                                                        for(auto itr10 = itr9->value.Begin();itr10 != itr9->value.End();++itr10){
                                                                                                                                                                            if(itr10->IsObject()){
                                                                                                                                                                                for(auto itr11 =itr10->GetObject().MemberBegin();itr11 !=itr10->GetObject().MemberEnd();++itr11){
                                                                                                                                                                                    if((itr11+1)->value.IsString()&&(itr11+1)->value=="kExpression"){
                                                                                                                                                                                        if(itr11->value.IsArray()){
                                                                                                                                                                                            for(auto kExp = itr11->value.Begin(); kExp != itr11->value.End();++kExp){
                                                                                                                                                                                                if(kExp->IsObject()){
                                                                                                                                                                                                    for(auto kNumber = kExp->GetObject().MemberBegin();kNumber != kExp->GetObject().MemberEnd();++kNumber){
                                                                                                                                                                                                        if((kNumber+1)->value.IsString() && (kNumber+1)->value=="kNumber"){
                                                                                                                                                                                                            for(auto decNum = kNumber->value.Begin();decNum != kNumber->value.End();++decNum){
                                                                                                                                                                                                                if(decNum->IsObject()){
                                                                                                                                                                                                                    for(auto wideNum = decNum->GetObject().MemberBegin();wideNum != decNum->GetObject().MemberEnd();++wideNum){
                                                                                                                                                                                                                        if(wideNum->name=="text"){
                                                                                                                                                                                                                            cout <<wideNum->value.GetString()<<endl;
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
                                                                                                    }else if((itr-1)->value.IsArray()&&itr->value=="kNetVariableDeclarationAssign"){
                                                                                                        for(auto itr2 = (itr-1)->value.Begin();itr2 !=(itr-1)->value.End();++itr2){
                                                                                                            if(itr2->IsObject()){
                                                                                                                for(auto itr3 = itr2->GetObject().MemberBegin();itr3 != itr2->GetObject().MemberEnd();++itr3){
                                                                                                                    if(itr3->value.IsArray() && (itr3+1)->value == "kNetVariable")
                                                                                                                        for(auto itr4 = itr3->value.Begin();itr4 != itr3->value.End();++itr4){
                                                                                                                            if(itr4->IsObject()){
                                                                                                                                for(auto itr5 = itr4->GetObject().MemberBegin();itr5 != itr4->GetObject().MemberEnd();++itr5){
                                                                                                                                    if(itr5->value.IsString()&&itr5->value=="SymbolIdentifier"&&(itr5+1)->name=="text"){
                                                                                                                                        cout << (itr5+1)->value.GetString()<<endl;
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
//
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }else if(ModuleItem->value == "kDataDeclaration"&&(ModuleItem-1)->value.IsArray()){
                                                                                    if((ModuleItem-1)->value.IsArray()){
                                                                                        for(auto itr = (ModuleItem-1)->value.Begin();itr!=(ModuleItem-1)->value.End();++itr){
                                                                                            if(itr->IsObject()){
                                                                                                for(auto itr1 = itr->GetObject().MemberBegin();itr1 != itr->GetObject().MemberEnd();++itr1){
                                                                                                    if((itr1+1)->value=="kInstantiationBase" && itr1->value.IsArray()){
                                                                                                        for(auto itr2 = itr1->value.Begin();itr2!=itr1->value.End();++itr2){
                                                                                                            if(itr2->IsObject()){
                                                                                                                for(auto itr3 = itr2->GetObject().MemberBegin();itr3 !=itr2->GetObject().MemberEnd();++itr3){
                                                                                                                    if(itr3->value.IsArray() && (itr3+1)->value=="kInstantiationType"){
                                                                                                                        //cout<<(itr3+1)->value.GetString()<<endl;
                                                                                                                        for(auto itr4 = itr3->value.Begin();itr4 != itr3->value.End();++itr4){
                                                                                                                            if(itr4->IsObject()){
                                                                                                                                for(auto itr5 = itr4->GetObject().MemberBegin();itr5 != itr4->GetObject().MemberEnd();++itr5){
                                                                                                                                    if(itr5->value.IsArray() && (itr5+1)->value == "kDataType"){
                                                                                                                                        for(auto itr6 = itr5->value.Begin(); itr6 != itr5->value.End();++itr6){
                                                                                                                                            if(itr6->IsObject()){
                                                                                                                                                for(auto itr7 = itr6->GetObject().MemberBegin();itr7 != itr6->GetObject().MemberEnd();++itr7){
                                                                                                                                                    if(itr7->value.IsArray()&&(itr7+1)->value=="kDataTypePrimitive"){
                                                                                                                                                        for(auto itr8 = itr7->value.Begin(); itr8 != itr7->value.End();++itr8){
                                                                                                                                                            if(itr8->IsObject()){
                                                                                                                                                                for(auto DataType = itr8->GetObject().MemberBegin();DataType != itr8->GetObject().MemberEnd();++DataType){
                                                                                                                                                                    if(DataType->value.IsString()){
                                                                                                                                                                        //reg
                                                                                                                                                                        cout<<DataType->value.GetString()<<endl;
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }else if(itr7->value.IsArray()&&(itr7+1)->value=="kPackedDimensions"){
                                                                                                                                                        for(auto itr8 = itr7->value.Begin();itr8 != itr7->value.End();++itr8){
                                                                                                                                                            if(itr8->IsObject()){
                                                                                                                                                                for(auto itr9 = itr8->GetObject().MemberBegin();itr9 != itr8->GetObject().MemberEnd();++itr9){
                                                                                                                                                                    if(itr9->value.IsArray()){
                                                                                                                                                                        for(auto itr10 = itr9->value.Begin();itr10 != itr9->value.End();++itr10){
                                                                                                                                                                            if(itr10->IsObject()){
                                                                                                                                                                                for(auto itr11=itr10->GetObject().MemberBegin();itr11!=itr10->GetObject().MemberEnd();++itr11){
                                                                                                                                                                                    if(itr11->value.IsArray()){
                                                                                                                                                                                        for(auto itr12 = itr11->value.Begin();itr12 != itr11->value.End();++itr12){
                                                                                                                                                                                            if(itr12->IsObject()){
                                                                                                                                                                                                //repair
                                                                                                                                                                                                for(auto itr13 =itr12->GetObject().MemberBegin();itr13 !=itr12->GetObject().MemberEnd();++itr13){
                                                                                                                                                                                                    if((itr13+1)->value.IsString()&&(itr13+1)->value=="kExpression"){
                                                                                                                                                                                                        if(itr13->value.IsArray()){
                                                                                                                                                                                                            for(auto kExp = itr13->value.Begin(); kExp != itr13->value.End();++kExp){
                                                                                                                                                                                                                if(kExp->IsObject()){
                                                                                                                                                                                                                    for(auto kNumber = kExp->GetObject().MemberBegin();kNumber != kExp->GetObject().MemberEnd();++kNumber){
                                                                                                                                                                                                                        if((kNumber+1)->value.IsString() && (kNumber+1)->value=="kNumber"){
                                                                                                                                                                                                                            for(auto decNum = kNumber->value.Begin();decNum != kNumber->value.End();++decNum){
                                                                                                                                                                                                                                if(decNum->IsObject()){
                                                                                                                                                                                                                                    for(auto wideNum = decNum->GetObject().MemberBegin();wideNum != decNum->GetObject().MemberEnd();++wideNum){
                                                                                                                                                                                                                                        if(wideNum->name=="text"){
                                                                                                                                                                                                                                            cout <<wideNum->value.GetString()<<endl;
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
                                                                                                                                                    }else if(itr7->value.IsArray() && (itr7+1)->value=="kUnqualifiedId"){
                                                                                                                                                        for(auto itr8=itr7->value.Begin();itr8!=itr7->value.End();++itr8){
                                                                                                                                                            if(itr8->IsObject()){
                                                                                                                                                                for(auto itr9 = itr8->GetObject().MemberBegin();itr9 != itr8->GetObject().MemberEnd();++itr9){
                                                                                                                                                                    //get inst
                                                                                                                                                                    if(itr9->value.IsString() && itr9->value =="SymbolIdentifier" &&(itr9+1)->name == "text"){
                                                                                                                                                                        cout<<(itr9+1)->value.GetString()<<endl;
                                                                                                                                                                    }else if(itr9->value.IsString()&& itr9->value == "kActualParameterList" &&(itr9-1)->value.IsArray()){
                                                                                                                                                                        for(auto itr10 = (itr9-1)->value.Begin();itr10 != (itr9-1)->value.End();++itr10){
                                                                                                                                                                            if(itr10->IsObject()){
                                                                                                                                                                                for(auto itr11 = itr10->GetObject().MemberBegin();itr11 != itr10->GetObject().MemberEnd();++itr11){
                                                                                                                                                                                    if((itr11+1)->value == "kParenGroup" && itr11->value.IsArray()){
                                                                                                                                                                                        for(auto itr12 = itr11->value.Begin();itr12 != itr11->value.End();++itr12){
                                                                                                                                                                                            if(itr12->IsObject()){
                                                                                                                                                                                                for(auto itr13 = itr12->GetObject().MemberBegin();itr13 != itr12->GetObject().MemberEnd();++itr13){
                                                                                                                                                                                                    if(itr13->value.IsArray()&&(itr13+1)->value == "kActualParameterByNameList"){
                                                                                                                                                                                                        for(auto itr14 = itr13->value.Begin();itr14 != itr13->value.End();++itr14){
                                                                                                                                                                                                            if(itr14->IsObject()){
                                                                                                                                                                                                                for(auto itr15 = itr14->GetObject().MemberBegin();itr15 != itr14->GetObject().MemberEnd();++itr15){
                                                                                                                                                                                                                    if(itr15->value.IsArray()&&(itr15+1)->value == "kParamByName"){
                                                                                                                                                                                                                        //cout<<(itr15+1)->value.GetString()<<endl;
                                                                                                                                                                                                                        // repair
                                                                                                                                                                                                                        for(auto itr16=itr15->value.Begin();itr16!=itr15->value.End();++itr16){
                                                                                                                                                                                                                            if(itr16->IsObject()) {
                                                                                                                                                                                                                                for (auto itr17 = itr16->GetObject().MemberBegin();itr17 !=itr16->GetObject().MemberEnd(); ++itr17) {
                                                                                                                                                                                                                                    //get inst
                                                                                                                                                                                                                                    if(itr17->value.IsString() && itr17->value == "."){
                                                                                                                                                                                                                                        cout <<itr17->value.GetString();
                                                                                                                                                                                                                                    } else if (itr17->value.IsString() &&itr17->value =="SymbolIdentifier" &&(itr17 +1)->name =="text") {
                                                                                                                                                                                                                                        cout<<(itr17 +1)->value.GetString()<< endl;
                                                                                                                                                                                                                                        //repair
                                                                                                                                                                                                                                    }else if(itr17->value.IsString() && itr17->value =="kParenGroup" &&(itr17 -1)->value.IsArray()){
                                                                                                                                                                                                                                        for(auto itr18 = (itr17 -1)->value.Begin();itr18 != (itr17 -1)->value.End();++itr18){
                                                                                                                                                                                                                                            if(itr18->IsObject()){
                                                                                                                                                                                                                                                for(auto itr19 = itr18->GetObject().MemberBegin();itr19 != itr18->GetObject().MemberEnd();++itr19){
                                                                                                                                                                                                                                                    if(itr19->value.IsArray()&&(itr19+1)->value=="kExpression"){
                                                                                                                                                                                                                                                        //cout << (itr19+1)->value.GetString()<<endl;
                                                                                                                                                                                                                                                        for(auto itr20 = itr19->value.Begin();itr20!=itr19->value.End();++itr20){
                                                                                                                                                                                                                                                            if(itr20->IsObject()){
                                                                                                                                                                                                                                                                for(auto itr21 = itr20->GetObject().MemberBegin();itr21 != itr20->GetObject().MemberEnd();++itr21){
                                                                                                                                                                                                                                                                    if((itr21+1)->value=="kReferenceCallBase"&&itr21->value.IsArray()){
                                                                                                                                                                                                                                                                        for(auto itr22 = itr21->value.Begin();itr22!=itr21->value.End();++itr22){
                                                                                                                                                                                                                                                                            if(itr22->IsObject()){
                                                                                                                                                                                                                                                                                for(auto itr23 = itr22->GetObject().MemberBegin();itr23 != itr22->GetObject().MemberEnd();++itr23){
                                                                                                                                                                                                                                                                                    if((itr23+1)->value.IsString()&&(itr23+1)->value=="kReference" &&itr23->value.IsArray()){
                                                                                                                                                                                                                                                                                        //cout<<(itr23+1)->value.GetString()<<endl;
                                                                                                                                                                                                                                                                                        for(auto itr24 = itr23->value.Begin();itr24 != itr23->value.End();++itr24){
                                                                                                                                                                                                                                                                                            if(itr24->IsObject()){
                                                                                                                                                                                                                                                                                                for(auto itr25 = itr24->GetObject().MemberBegin();itr25!= itr24->GetObject().MemberEnd();++itr25){
                                                                                                                                                                                                                                                                                                    if((itr25+1)->value.IsString()&&(itr25+1)->value=="kLocalRoot"&&itr25->value.IsArray()){
                                                                                                                                                                                                                                                                                                        for(auto itr26 = itr25->value.Begin();itr26 != itr25->value.End();++itr26){
                                                                                                                                                                                                                                                                                                            if(itr26->IsObject()){
                                                                                                                                                                                                                                                                                                                for(auto itr27 = itr26->GetObject().MemberBegin();itr27 != itr26->GetObject().MemberEnd();++itr27){
                                                                                                                                                                                                                                                                                                                    if((itr27+1)->value.IsString()&&itr27->value.IsArray()&&(itr27+1)->value=="kUnqualifiedId"){
                                                                                                                                                                                                                                                                                                                        for(auto itr28 = itr27->value.Begin();itr28!=itr27->value.End();++itr28){
                                                                                                                                                                                                                                                                                                                            if(itr28->IsObject()){
                                                                                                                                                                                                                                                                                                                                for(auto InstName = itr28->GetObject().MemberBegin();InstName != itr28->GetObject().MemberEnd();++InstName){
                                                                                                                                                                                                                                                                                                                                    if(InstName->value.IsString()&&InstName->value=="SymbolIdentifier"&&(InstName+1)->name=="text"){
                                                                                                                                                                                                                                                                                                                                        cout << (InstName+1)->value.GetString()<<endl;
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
                                                                                                                    } else if(itr3->value.IsArray() && (itr3+1)->value=="kGateInstanceRegisterVariableList"){
                                                                                                                        for(auto itr4 = itr3->value.Begin();itr4 !=itr3->value.End();++itr4){
                                                                                                                            if(itr4->IsObject()){
                                                                                                                                for(auto itr5 = itr4->GetObject().MemberBegin();itr5 != itr4->GetObject().MemberEnd();++itr5){
                                                                                                                                    if(itr5->value.IsArray() && (itr5+1)->value == "kRegisterVariable"){
                                                                                                                                        for(auto itr6 = itr5->value.Begin();itr6 != itr5->value.End();++itr6){
                                                                                                                                            if(itr6->IsObject()){
                                                                                                                                                for(auto itr7 = itr6->GetObject().MemberBegin();itr7 != itr6->GetObject().MemberEnd();++itr7){
                                                                                                                                                    if(itr7->value.IsString()&&itr7->value=="SymbolIdentifier"&&(itr7+1)->name=="text"){
                                                                                                                                                        cout << (itr7+1)->value.GetString()<<endl;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }else if(itr5->value.IsArray() && (itr5+1)->value == "kGateInstance"){
                                                                                                                                        for(auto itr6 = itr5->value.Begin();itr6 != itr5->value.End();++itr6){
                                                                                                                                            if(itr6->IsObject()){
                                                                                                                                                for(auto itr7 = itr6->GetObject().MemberBegin();itr7 != itr6->GetObject().MemberEnd();++itr7){
                                                                                                                                                    if(itr7->value.IsString()&&itr7->value=="SymbolIdentifier"&&(itr7+1)->name == "text"){
                                                                                                                                                        // inst module name
                                                                                                                                                        cout <<(itr7+1)->value.GetString()<<endl;
                                                                                                                                                    }
                                                                                                                                                    else if(itr7->value.IsArray() && (itr7+1)->value=="kParenGroup"){
                                                                                                                                                        for(auto itr8 = itr7->value.Begin();itr8 != itr7->value.End();++itr8){
                                                                                                                                                            if(itr8->IsObject()){
                                                                                                                                                                for(auto itr9 = itr8->GetObject().MemberBegin();itr9 != itr8->GetObject().MemberEnd();++itr9){
                                                                                                                                                                    if(itr9->value.IsArray()&&(itr9+1)->value=="kPortActualList"){
                                                                                                                                                                        //cout<<(itr9+1)->value.GetString()<<endl;
                                                                                                                                                                        for(auto itr10 = itr9->value.Begin();itr10 != itr9->value.End();++itr10){
                                                                                                                                                                            if(itr10->IsObject()){
                                                                                                                                                                                for (auto itr11 = itr10->GetObject().MemberBegin();itr11 != itr10->GetObject().MemberEnd();++itr11){
                                                                                                                                                                                    if(itr11->value.IsArray()&&(itr11+1)->value=="kActualNamedPort"){
                                                                                                                                                                                        //cout << (itr11+1)->value.GetString()<<endl;
                                                                                                                                                                                        for(auto itr12 = itr11->value.Begin();itr12 != itr11->value.End();++itr12){
                                                                                                                                                                                            if(itr12->IsObject()){
                                                                                                                                                                                                for(auto itr13 = itr12->GetObject().MemberBegin();itr13 != itr12->GetObject().MemberEnd();++itr13){
                                                                                                                                                                                                    if(itr13->value.IsString() && itr13->value == "."){
                                                                                                                                                                                                        cout <<itr13->value.GetString();
                                                                                                                                                                                                    }
                                                                                                                                                                                                    else if(itr13->value.IsString()&&itr13->value=="SymbolIdentifier"&&(itr13+1)->name == "text"){
                                                                                                                                                                                                        // inst port name
                                                                                                                                                                                                        cout <<(itr13+1)->value.GetString()<<endl;
                                                                                                                                                                                                    }else if(itr13->value.IsArray() && (itr13+1)->value=="kParenGroup"){
                                                                                                                                                                                                        for(auto itr14 = itr13->value.Begin(); itr14 != itr13->value.End();++itr14){
                                                                                                                                                                                                            if(itr14->IsObject()){
                                                                                                                                                                                                                for(auto itr15 = itr14->GetObject().MemberBegin();itr15 != itr14->GetObject().MemberEnd();++itr15){
                                                                                                                                                                                                                    if(itr15->value.IsArray()&&(itr15+1)->value=="kExpression"){
                                                                                                                                                                                                                        //repair
                                                                                                                                                                                                                        for(auto itr16 = itr15->value.Begin();itr16!=itr15->value.End();++itr16){
                                                                                                                                                                                                                            if(itr16->IsObject()){
                                                                                                                                                                                                                                for(auto itr17 = itr16->GetObject().MemberBegin();itr17 != itr16->GetObject().MemberEnd();++itr17){
                                                                                                                                                                                                                                    if((itr17+1)->value=="kReferenceCallBase"&&itr17->value.IsArray()){
                                                                                                                                                                                                                                        for(auto itr18 = itr17->value.Begin();itr18!=itr17->value.End();++itr18){
                                                                                                                                                                                                                                            if(itr18->IsObject()){
                                                                                                                                                                                                                                                for(auto itr19 = itr18->GetObject().MemberBegin();itr19 != itr18->GetObject().MemberEnd();++itr19){
                                                                                                                                                                                                                                                    if((itr19+1)->value.IsString()&&(itr19+1)->value=="kReference" &&itr19->value.IsArray()){
                                                                                                                                                                                                                                                        //cout<<(itr23+1)->value.GetString()<<endl;
                                                                                                                                                                                                                                                        for(auto itr20 = itr19->value.Begin();itr20 != itr19->value.End();++itr20){
                                                                                                                                                                                                                                                            if(itr20->IsObject()){
                                                                                                                                                                                                                                                                for(auto itr21 = itr20->GetObject().MemberBegin();itr21!= itr20->GetObject().MemberEnd();++itr21){
                                                                                                                                                                                                                                                                    if((itr21+1)->value.IsString()&&(itr21+1)->value=="kLocalRoot"&&itr21->value.IsArray()){
                                                                                                                                                                                                                                                                        for(auto itr22 = itr21->value.Begin();itr22 != itr21->value.End();++itr22){
                                                                                                                                                                                                                                                                            if(itr22->IsObject()){
                                                                                                                                                                                                                                                                                for(auto itr23 = itr22->GetObject().MemberBegin();itr23 != itr22->GetObject().MemberEnd();++itr23){
                                                                                                                                                                                                                                                                                    if((itr23+1)->value.IsString()&&itr23->value.IsArray()&&(itr23+1)->value=="kUnqualifiedId"){
                                                                                                                                                                                                                                                                                        for(auto itr24 = itr23->value.Begin();itr24!=itr23->value.End();++itr24){
                                                                                                                                                                                                                                                                                            if(itr24->IsObject()){
                                                                                                                                                                                                                                                                                                for(auto InstName = itr24->GetObject().MemberBegin();InstName != itr24->GetObject().MemberEnd();++InstName){
                                                                                                                                                                                                                                                                                                    if(InstName->value.IsString()&&InstName->value=="SymbolIdentifier"&&(InstName+1)->name=="text"){
                                                                                                                                                                                                                                                                                                        cout << (InstName+1)->value.GetString()<<endl;
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


    //fclose(fp);

    return 0;
}
