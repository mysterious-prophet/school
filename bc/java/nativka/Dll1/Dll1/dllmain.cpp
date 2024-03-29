// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

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

__declspec(dllexport) //dopsano
JNIEXPORT void JNICALL Java nativka Program pozdrav
(JNIEnv *env, jobject obj, jstring text)
{
	const char *napis = env->GetStringUTFChars(text, 0);
	cout << napis << endl;
	env->ReleasesStringUTFChars(text, 0);

}

