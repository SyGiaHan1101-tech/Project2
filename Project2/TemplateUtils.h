#ifndef TEMPLATEUTILS_H
#define TEMPLATEUTILS_H
#include <cstddef>

template <typename T>
void hoanDoi(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void sapXepTheoUsername(T& ds)
{
    for (size_t i = 0; i < ds.size(); i++)
    {
        for (size_t j = i + 1; j < ds.size(); j++)
        {
            if (ds[i].getUsername() > ds[j].getUsername())
            {
                hoanDoi(ds[i], ds[j]);
            }
        }
    }
}

#endif