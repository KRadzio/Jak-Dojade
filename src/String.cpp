#include "String.hpp"
#define BUFFERSIZE 512
#define DELIMITER '\n'

std::ostream &operator<<(std::ostream &os, String &s)
{
    os << s.tab;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    char buff[BUFFERSIZE];
    is.getline(buff, BUFFERSIZE);
    int buffInd = 0;
    s.length = 0;
    if (s.tab != nullptr)
        delete[] s.tab;
    while (buff[buffInd] != '\0')
    {
        s.length++;
        buffInd++;
    }
    s.tab = new char[s.length + 1];
    int i = 0;
    while (i < s.length)
    {
        s.tab[i] = buff[i];
        i++;
    }
    s.tab[i] = '\0';
    return is;
}

String::String() : length(0), tab(nullptr)
{
    tab = new char[1];
    tab[0] = '\0';
}

String::String(int length) : length(length), tab(nullptr)
{
    tab = new char[length + 1];
    tab[length] = '\0';
}

String::String(const char *s)
{
    length = strlen(s);
    tab = new char[length + 1];
    strcpy(tab, s);
    tab[length] = '\0';
}

String::String(const String &other)
{
    length = other.length;
    tab = new char[length + 1];
    strcpy(tab, other.tab);
    tab[length] = '\0';
}

String &String::operator=(const String &other)
{
    if (tab != nullptr)
        delete[] tab;
    length = other.length;
    tab = new char[length + 1];
    strcpy(tab, other.tab);
    tab[length] = '\0';
    return *this;
}

String &String::operator=(const char *s)
{
    length = strlen(s);
    delete[] tab;
    tab = new char[length + 1];
    strcpy(tab, s);
    tab[length] = '\0';
    return *this;
}

String &String::operator+(char c)
{
    length++;
    char *newTab = new char[length + 1];
    for (int i = 0; i < length - 1; i++)
    {
        newTab[i] = tab[i];
    }
    newTab[length - 1] = c;
    newTab[length] = '\0';
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+(const char *s)
{
    int prevLen = length;
    length += strlen(s);
    char *newTab = new char[length + 1];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = s[i - prevLen];
    }
    newTab[length] = '\0';
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+(const String &other)
{
    int prevLen = length;
    length += other.length;
    char *newTab = new char[length + 1];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = other.tab[i - prevLen];
    }
    newTab[length] = '\0';
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+=(const char *s)
{
    int prevLen = length;
    length += strlen(s);
    char *newTab = new char[length + 1];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = s[i - prevLen];
    }
    newTab[length] = '\0';
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+=(const String &other)
{
    int prevLen = length;
    length += other.length;
    char *newTab = new char[length + 1];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = other.tab[i - prevLen];
    }
    newTab[length] = '\0';
    delete[] tab;
    tab = newTab;
    return *this;
}

bool String::operator==(const String &other) const
{
    if (other.length != this->length)
        return false;
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            if (other.tab[i] != this->tab[i])
                return false;
        }
        return true;
    }
}

bool String::operator!=(const String &other) const
{
    if (other.length != this->length)
        return true;
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            if (other.tab[i] != this->tab[i])
                return true;
        }
        return false;
    }
}

bool String::operator==(const char *s) const
{
    if (length != (int)strlen(s))
        return false;
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            if (s[i] != this->tab[i])
                return false;
        }
        return true;
    }
}

char String::operator[](const int index) const
{
    if (index < length && index > -1)
        return this->tab[index];
    else
        return NULL;
}

String String::subStr(int begin, char separator) const
{
    int i = begin;
    String subS;
    int newLength = 0;
    while (tab[i] != separator)
    {
        newLength++;
        if (i == length && tab[i] != separator)
        {
            subS = "";
            return subS;
        }
        i++;
    }
    subS.length = newLength;
    subS.tab = new char[subS.length + 1];
    int j = 0;
    while (j + begin < begin + newLength)
    {
        subS.tab[j] = tab[j + begin];
        j++;
    }
    subS.tab[j] = '\0';
    return subS;
}

bool String::isANumber() const
{
    int i = 0;
    while (i < length)
    {
        if (tab[i] < 48 || tab[i] > 57)
            return false;
        i++;
    }
    return true;
}

int String::stoi()
{
    if (length > 0 && isANumber())
        return atoi(tab);
    else
        return NULL;
}

bool String::isCharInsideString(char chr) const
{
    int i = 0;
    while (tab[i] != '\0')
    {
        if (tab[i] == chr)
            return true;
        i++;
    }
    return false;
}

int String::getLength() const { return this->length; }

void String::setTabIndex(int i, char c)
{
    if (i > -1 && i < this->length)
        this->tab[i] = c;
}

void String::setLength(int newLength) { this->length = newLength; }

String::~String()
{
    if (tab != nullptr)
        delete[] tab;
}