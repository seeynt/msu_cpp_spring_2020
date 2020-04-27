#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
    std::mutex mutex_;
    std::condition_variable cv;

    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

public:
    explicit ThreadPool(std::size_t poolSize) {
        for (std::size_t i = 0; i < poolSize; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    this->cv.wait(lock, [this]{ return !this->tasks.empty(); });

                    if(this->tasks.empty())
                        return;

                    auto task = std::move(this->tasks.front());
                    this->tasks.pop();

                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv.notify_all();
        for (std::thread &thread_: threads)
            thread_.detach();
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto pack = std::make_shared<std::packaged_task<decltype(func(args...))()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::unique_lock<std::mutex> lock(mutex_);

        tasks.emplace([pack](){ (*pack)(); });
        cv.notify_one();

        return pack->get_future();
    }
};
