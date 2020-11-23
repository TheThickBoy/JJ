#include "tString.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
using namespace std;

TString::TString(const char *s) : ptr(nullptr), len(0)
{
    if (s != nullptr)
    {
        len = strlen(s);
        ptr = new char[len + 1]; 
        strcpy(ptr, s);
    }

    cout << "TString c-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
}

TString::~TString()
{

    cout << "TString d-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;

    delete[] ptr;
}
TString::TString(const TString &s) : ptr(nullptr), len(s.len)
{
    if (len > 0)
    {
        ptr = new char[len + 1];
        strcpy(ptr, s.ptr);
    }

    cout << "TString cc-tor: [" << (ptr ? ptr : "pusty") << "]" << endl;
}

TString &TString::operator=(const TString &s)
{

    if (this != &s)
    { 

        delete[] ptr;
        ptr = nullptr;
        len = s.len;
        if (len > 0)
        {
            ptr = new char[len + 1];
            strcpy(ptr, s.ptr);
        }
    }

    cout << "TString copy operator=: [" << (ptr ? ptr : "pusty") << "]" << endl;

    return *this;
}

TString::TString(TString &&s) : ptr(s.ptr), len(s.len)
{
    s.ptr = nullptr;
    s.len = 0;

    cout << "TString operator=: [" << (ptr ? ptr : "pusty") << "]" << endl;
}

TString &TString::operator=(TString &&s)
{

    if (this != &s)
    {
        delete[] ptr;
        len = s.len;
        ptr = s.ptr;
        s.len = 0;
        s.ptr = nullptr;
    }

    cout << "TString move operator=: [" << (ptr ? ptr : "pusty") << "]" << endl;

    return *this;
}

char &TString::operator[](size_t n)
{
    if (ptr == nullptr)
        throw "pusty obiekt";

    if (n < len)
        return ptr[n];

    throw out_of_range("In TString operator [] argument out of range");
}

const char &TString::operator[](size_t n) const
{

    if (ptr == nullptr)
        throw "pusty obiekt";

    if (n < len)
        return ptr[n];

    throw out_of_range("In TString operator [] argument out of range");
}

char *TString::insert(size_t pos, const char *c)
{

    if (pos <= len)
    {
        size_t oldlen = len;
        len = len + strlen(c);
        char *tmp = new char[len + 1];
        strcpy(tmp, ptr);
        for (size_t i = pos; i < pos + strlen(c); ++i)
        {
            tmp[i] = c[i - pos];
        }
        for (size_t i = pos; i < oldlen; ++i)
        {
            tmp[i + strlen(c)] = ptr[i];
        }
        delete[] ptr;
        ptr = tmp;
        return ptr + pos;
    }
    else
    {
        throw out_of_range("In TString insert(pos, *) argument out of range");
    }
    return ptr;
}

char *TString::insert(size_t pos, char c)
{

    return insert(pos, string({c}).c_str());
}

char *TString::erase(size_t bpos, size_t leng)
{

    if (bpos <= len && bpos >= 0 && leng < len - bpos)
    {
        char *tmp = new char[len];
        strcpy(tmp, ptr);
        for (size_t i = bpos; i <= len; ++i)
        {
            if (i + leng <= len - bpos)
            {
                tmp[i] = tmp[i + leng];
            }
        }
        delete[] ptr;
        len = len - leng;
        ptr = tmp;
    }
    else
    {
        throw out_of_range("In TString erase(bpos, *) argument out of range");
    }

    return ptr;
}
