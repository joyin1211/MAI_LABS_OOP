#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

template <typename T>
class DispatchQueue {
public:
    using Handler = std::function<void(const T&)>;

    void start(Handler h) {
        handler = std::move(h);
        running = true;
        worker = std::thread([this] { loop(); });
    }

    void dispatch(const T& task) {
        std::lock_guard<std::mutex> lg(mtx);
        q.push(task);
        cv.notify_one();
    }

    void stop() {
        running = false;
        cv.notify_all();
        if (worker.joinable()) {
            worker.join();
        }
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> running{false};
    Handler handler;

    void loop() {
        while (running) {
            T task;
            {
                std::unique_lock<std::mutex> ul(mtx);
                cv.wait(ul, [&] { 
                    return !q.empty() || !running; 
                });
                if (!running && q.empty()) {
                    return;
                }
                task = q.front();
                q.pop();
            }
            handler(task);
        }
    }
};
