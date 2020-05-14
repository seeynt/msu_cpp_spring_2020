#include "sum.h"

static int result = 0;

static int sum_line(const std::string line) {
	std::stringstream ss(line);
	std::mutex mutex_;
	int sum = 0, val;
	while (ss >> val)
		sum += val;

	{
		std::unique_lock<std::mutex> lock(mutex_);
		result += sum;
		sum = result;
	}

	return sum;
}

int sum_file(const std::string& fname) {
	std::string line;
	result = 0;
	int ans = 0;
	ThreadPool pool(2);

	std::ifstream fin("test.txt");
	while (std::getline(fin, line)) {
		auto task = pool.exec(sum_line, line);
		ans = task.get();
	}

	std::cout << ans << std::endl;
	return ans;
}