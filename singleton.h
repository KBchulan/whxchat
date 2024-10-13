/******************************************************************************
 *
 * @file       singleton.h
 * @brief      单例模板类实现
 *
 * @author     KBchulan
 * @date       2024/10/11
 * @history
 *****************************************************************************/
#ifndef SINGLETON_H
#define SINGLETON_H

#include "global.h"

template <typename T>
class Singleton
{
public:
    virtual ~Singleton()
    {
        std::cout << "this singleton is be destroied" << std::endl;
    }

    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&](){
            // make_shared会调用构造函数，而此处为私有化
            instance = std::shared_ptr<T>(new T);
        });
        return instance;
    }

    void PrintAddress()
    {
        std::cout << instance.get() << std::endl;
    }

protected:
    inline static std::shared_ptr<T> instance = nullptr;

protected:
    Singleton() = default;
    explicit Singleton(const Singleton<T> &) = delete;
    Singleton& operator = (const Singleton<T> &st) = delete;
};

#endif // SINGLETON_H
