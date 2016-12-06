#ifndef GENERAL_H
#define GENERAL_H
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
/* This GENERAL header is mainly for:
--Construct/Format Date + Time
--Generate Log file for KeyStroke recorder

--More functionalities
*/

namespace General
{

    template <class T>

    std::string ToString(const T &); //convert to STRING

    struct DateTime //structure Date and Time for local user time
    {
        DateTime()
        {
            time_t ms;
            time (&ms);

            struct tm *info = localtime(&ms);

            D = info->tm_mday;
            m = info->tm_mon + 1;
            y = 1900 + info->tm_year;
            H = info->tm_hour;
            M = info->tm_min;
            S = info->tm_sec;
        }

        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y),H(H), M(M), S(S){}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0) {}

        DateTime Now() const
        {
           return DateTime();
        }

        int D, m, y, H, M, S;

        std::string GetDateString() const //Return Date DD::MM::YYYY
        {
            return std::string(D < 10 ? "0" : "") + ToString(D) +
                   std::string(m < 10 ? ".0" : ".") + ToString(m) + "."
                   +ToString(y);
        }

        std::string GetTimeString(const std::string &sep = ":") const  // Return Time HH:MM:SS
        {
            return std::string(H < 10 ? "0" : "") + ToString(H) + sep +
                   std::string(M < 10 ? "0" : "") + ToString(M) + sep +
                   std::string(S < 10 ? "0" : "") + ToString(S);
        }

        std::string GetDateTimeString( const std::string &sep = ":")
        {
            return GetDateString() + " " + GetDateTimeString(sep);
        }
    };

    template <class T>

    std::string ToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();

    }

    void GenerateAppLog(const std::string &l) // Writing Log File to "AppLog.txt"
    {
        std::ofstream file(("AppLog.txt"), std::ios::app);
        file << "[" << General::DateTime().GetDateString() << "]" << "\n" << l // Format [DD MM YYYY]
        << std::endl << "\n";

        file.close();  // close the file after writing
    }
}
#endif // HELPER_H
