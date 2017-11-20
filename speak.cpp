#include "stdafx.h"`
#include <sapi.h>`
#include <iostream>`
#include <string>`

std::wstring str_to_ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

int main(int argc, char* argv[]) 
{
    while(true) 
    {
        std::cout << "Enter some words: " << std::endl; std::cout << ">> ";
        std::string text; std::cin >> text;
        std::cout << "" << std::endl;
        std::wstring stemp = str_to_ws(text);
        LPCWSTR speech_text = stemp.c_str();
        ISpVoice * pVoice = NULL;
        if (FAILED(::CoInitialize(NULL))) {}
        HRESULT hresult = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
        if (SUCCEEDED(hresult)) 
        {
            hresult = pVoice->Speak(speech_text, 0, NULL); 
            pVoice->Release();
            pVoice = NULL;
        }
        ::CoUninitialize(); 
        return TRUE;
    }
}