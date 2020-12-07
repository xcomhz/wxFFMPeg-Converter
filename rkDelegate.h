#pragma once


#define DelegateFunction(Declaration) typedef  std::function<Declaration> 
#define BindCallback(AConStatusChanged,code) AConStatusChanged= [&]code
#define BuildCallbackConnector(MemberCallBack,InputTypesAndParams,Params) MemberCallBack = [&]InputTypesAndParams->void {FunctionParams; }
#define CreateConnector(FuncPointer,TypesAndParams,Params,Function)  FuncPointer = [&]TypesAndParams->void {Function Params; }


//Converter->OnOutputLineReceived = &cMain::OnOutputLineReceived;
