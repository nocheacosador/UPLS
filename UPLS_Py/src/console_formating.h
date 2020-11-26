#ifndef CONSOLE_FORMAT_H
#define CONSOLE_FORMAT_H

#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

class Format
{
public:
    enum class Color : uint8_t
    {
        Default = 39,
        Black   = 30,
        Red     = 31,
        Green   = 32,
        Yellow  = 33,
        Blue    = 34,
        Magenta = 35,
        Cyan    = 36,
        White   = 37,
        Gray          = 90,
        BrightRed     = 91,
        BrightGreen   = 92,
        BrightYellow  = 93,
        BrightBlue    = 94,
        BrightMagenta = 95,
        BrightCyan    = 96,
        BrightWhite   = 97
    };

    Format() : m_reset(true), m_textSet(false), m_text(nullptr) { ; }
    Format(const char* string)  : m_reset(false), m_textSet(true)
    {
        size_t size = 0;
        while (string[size++] != '\0') { ; }
        m_text = new char[size];
        memcpy(m_text, string, size);
    }

    Format(const std::string& string)  : m_reset(false), m_textSet(true)
    {
        m_text = new char[string.size()];
        memcpy(m_text, string.c_str(), string.size());
    }

    ~Format()
    {
        if (m_text) delete[] m_text;
    }

    Format& foreground(const Color color)
    {
        m_reset = false;
        m_codes.push_back(static_cast<uint8_t>(color));
        return *this;
    }

    Format& color(const Color color)
    {
        m_reset = false;
        m_codes.push_back(static_cast<uint8_t>(color));
        return *this;
    }

    Format& background(Color color)
    {
        m_reset = false;
        m_codes.push_back(static_cast<uint8_t>(color) + 10);
        return *this;
    }

    Format& backColor(Color color)
    {
        m_reset = false;
        m_codes.push_back(static_cast<uint8_t>(color) + 10);
        return *this;
    }

    Format& bold()
    {
        m_reset = false;
        m_codes.push_back(1);
        return *this;
    }

    Format& inverse()
    {
        m_reset = false;
        m_codes.push_back(7);
        return *this;
    }

    Format& underline()
    {
        m_reset = false;
        m_codes.push_back(4);
        return *this;
    }

    Format& doubleUnderline()
    {
        m_reset = false;
        m_codes.push_back(21);
        return *this;
    }

    Format& faint()
    {
        m_reset = false;
        m_codes.push_back(2);
        return *this;
    }

    Format& italic()
    {
        m_reset = false;
        m_codes.push_back(3);
        return *this;
    }

    Format& blink()
    {
        m_reset = false;
        m_codes.push_back(5);
        return *this;
    }

    Format& crossedout()
    {
        m_reset = false;
        m_codes.push_back(9);
        return *this;
    }

    Format& reset()
    {
        m_reset = true;
        m_textSet = false;
        if (m_text) delete[] m_text;
        m_text = nullptr;
        return *this;
    }

    Format& text(const std::string& string)
    {
        m_reset = false;
        m_textSet = true;

        if (m_text) delete[] m_text;
        m_text = new char[string.size()];
        memcpy(m_text, string.c_str(), string.size());

        return *this;
    }

    Format& text(const char* string)
    {
        m_reset = false;
        m_textSet = true;

        size_t size = 0;
        while (string[size++] != '\0') { ; }

        if (m_text) delete[] m_text;
        m_text = new char[size];
        memcpy(m_text, string, size);

        return *this;
    }

    std::string str() const
    {
        if (m_reset)
        {
            return "\033[0m";
        }
        else
        {
            std::stringstream ss;
            bool semicolonNeeded = false;

            ss << "\033[";

            for (auto& code : m_codes)
            {
                if (!semicolonNeeded)
                    semicolonNeeded = true;
                else
                    ss << ';';

                ss << int(code);
            }

            ss << 'm';

            if (m_textSet)
            {
                ss << m_text << "\033[0m";
            }

            return ss.str();
        }
    }

    friend std::ostream& operator << (std::ostream& os, const Format& obj)
    {
        if (obj.m_reset)
        {
            os << "\033[0m";
        }
        else
        {
            bool semicolonNeeded = false;

            os << "\033[";

            for (auto& code : obj.m_codes)
            {
                if (!semicolonNeeded)
                    semicolonNeeded = true;
                else
                    os << ';';

                os << int(code);
            }

            os << 'm';

            if (obj.m_textSet)
            {
                os << obj.m_text << "\033[0m";
            }
        }

        return os;
    }

private:
    bool  m_reset;
    bool  m_textSet;
    char* m_text;
    std::vector<uint8_t> m_codes;
};

typedef typename Format::Color Color;

#endif // CONSOLE_FORMAT_H
