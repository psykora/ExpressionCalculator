#pragma once

#include <string>

template <typename T>
class IUnaryFunc
{
public:
    virtual const std::string& symbol() const = 0;
    virtual T operator()(T arg1) const = 0;

public:
    virtual ~IUnaryFunc() {}
};

template <typename T>
class IBinaryFunc
{
public:
    virtual const std::string& symbol() const = 0;
    virtual T operator()(T arg1, T arg2) const = 0;

public:
    virtual ~IBinaryFunc() {}
};

template <typename T>
class UnaryFuncPlus : public IUnaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"+"};
        return s;
    };

    T operator()(T arg) const
    {
        return +arg;
    }
};

template <typename T>
class UnaryFuncMinus : public IUnaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"-"};
        return s;
    };

    T operator()(T arg) const
    {
        return -arg;
    }
};

template <typename T>
class BinaryFuncPlus : public IBinaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"+"};
        return s;
    };

    T operator()(T arg1, T arg2) const
    {
        return arg1 + arg2;
    }
};

template <typename T>
class BinaryFuncMinus : public IBinaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"-"};
        return s;
    };

    T operator()(T arg1, T arg2) const
    {
        return arg1 - arg2;
    }
};

template <typename T>
class BinaryFuncMultiply : public IBinaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"*"};
        return s;
    };

    T operator()(T arg1, T arg2) const
    {
        return arg1 * arg2;
    }
};

template <typename T>
class BinaryFuncDivide : public IBinaryFunc<T>
{
public:
    const std::string& symbol() const
    {
        static const std::string s{"/"};
        return s;
    };

    T operator()(T arg1, T arg2) const
    {
        return arg1 / arg2;
    }
};
