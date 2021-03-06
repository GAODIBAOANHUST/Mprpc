#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

// Mprpc框架提供的日志系统
// 异步写日志的日志队列
template <typename T>
class LockQueue
{
public:
    LockQueue(/* args */) = default;
    ~LockQueue() = default;

    // 多个Worker线程都会写日志queue
    void Push(const T& data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_cv.notify_one();
    }

    // 一个线程读日志queue
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this](){ return m_queue.size() > 0; });
        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
    
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};