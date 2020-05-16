#ifndef BUFFER_H
#define BUFFER_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class Buffer
{
public:
    void add(T &&data);
    T pop();
    void SetEndOfFile(bool status);
    bool EndOfBuffer();

private:
    std::deque<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::atomic<bool> end_of_file_{false};
    std::atomic<bool> end_of_buffer_{false};
};

template <typename T>
void Buffer<T>::add(T &&data)
{
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.emplace_back(std::move(data));
    condition_.notify_one();
}

template <typename T>
T Buffer<T>::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() { return !queue_.empty(); });

    auto to_return = std::move(queue_.front());
    queue_.pop_front();
    end_of_buffer_ = queue_.empty() && end_of_file_;
    return to_return;
}

template <typename T>
void Buffer<T>::SetEndOfFile(bool status)
{
    end_of_file_ = status;
}

template <typename T>
bool Buffer<T>::EndOfBuffer()
{
    return end_of_buffer_;
}

#endif