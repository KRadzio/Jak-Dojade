#pragma once
#include <iostream>
#include <string.h>

class String
{
private:
    int length;
    char *tab;

protected:
    friend std::ostream &operator<<(std::ostream &os, String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

public:
    String();
    String(int length);
    String(const char *s);
    String(const String &other);
    String &operator=(const String &other);
    String &operator=(const char *s);
    String &operator+(char c);
    String &operator+(const char *s);
    String &operator+(const String &other);
    String &operator+=(const char *s);
    String &operator+=(const String &other);
    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    bool operator==(const char *s) const;
    char operator[](const int index) const;
    String subStr(int begin, char separator) const;
    bool isCharInsideString(char chr) const;
    int getLength() const;
    bool isANumber() const;
    int stoi();
    void setTabIndex(int i, char c);
    void setLength(int newLength);
    ~String();
};