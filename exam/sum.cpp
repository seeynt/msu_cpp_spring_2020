#include "sum.h"

static int result = 0;
static bool stop = false;
static std::mutex mutex_;
static std::condition_variable cv;
static std::queue<std::string> lines;

static void sum_line() {
	std::string line;
	std::istringstream ss;
	int sum = 0, val;
	while (true) {
		{
			std::unique_lock<std::mutex> lock(mutex_);
        	cv.wait(lock, []() { return !lines.empty() || stop; });

            if (stop)
                return;

            line = std::move(lines.front());
            lines.pop();
        }

		ss.str(line);
		sum = 0;

		while (ss >> val)
			sum += val;

		{
			std::unique_lock<std::mutex> lock(mutex_);
			result += sum;
		}
	}
}

static void read_file(const std::string& fname) {
	std::ifstream fin(fname);
    std::string line;

	while (std::getline(fin, line)) {
		std::unique_lock<std::mutex> lock(mutex_);
		lines.push(line);
		cv.notify_one();
	}

	{
		std::unique_lock<std::mutex> lock(mutex_);
		stop = true;
		cv.notify_all();
	}

	return;
}

int sum_file(std::string fname) {
	result = 0, stop = false;
	std::vector<std::thread> sum_thread;

	std::thread read_thread(read_file, fname);

	for (int i = 0; i < 2; ++i)
		sum_thread.emplace_back(sum_line);

	read_thread.join();
	sum_thread[0].join();
	sum_thread[1].join();

	std::cout << result << std::endl;
	return result;
}