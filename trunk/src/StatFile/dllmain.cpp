// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

#include "StatFilePlugin.h"

CStatFilePlugin* g_pPlugin = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec( dllexport )  IPluginObj* __stdcall GetPluginObj(const std::string &strID) 
{
	g_pPlugin = new CStatFilePlugin(strID);
	return g_pPlugin;
}

