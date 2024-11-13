#include <iostream>
#include <limits>
#include <cstring>
#include <vector>
#include <csignal>

class IStatistics {
 public:
  virtual ~IStatistics() = default;

  virtual void update(double next) = 0;
  [[nodiscard]] virtual double eval() const = 0;
  [[nodiscard]] virtual const char *name() const = 0;
};

class Min : public IStatistics {
 public:
  Min() : m_min{std::numeric_limits<double>::max()} {
  }

  void update(double next) override {
	if (next < m_min) {
	  m_min = next;
	}
  }

  [[nodiscard]] double eval() const override {
	return m_min;
  }

  [[nodiscard]] const char *name() const override {
	return "min";
  }

 private:
  double m_min;
};

class Max : public IStatistics {
 public:
  Max() : m_max{std::numeric_limits<double>::min()} {
  }

  void update(double next) override {
	if (next > m_max) {
	  m_max = next;
	}
  }

  [[nodiscard]] double eval() const override {
	return m_max;
  }

  [[nodiscard]] const char *name() const override {
	return "max";
  }

 private:
  double m_max = 0;
};

class Mean : public IStatistics {
 public:
  Mean() : m_mean{std::numeric_limits<double>::min()} {
  }

  void update(double next) override {
	m_values.push_back(next);

  }

  [[nodiscard]] double eval() const override {
	double tmp = 0;
	for (auto m_value : m_values) {
	  tmp += m_value;
	}

	return tmp/m_values.size();
  }

  [[nodiscard]] const char *name() const override {
	return "mean";
  }

 private:
  std::vector<double> m_values;
  double m_mean;
};

std::sig_atomic_t sig_value = 0;

void handler(int sig) {
  sig_value = sig;
}

int main() {


  std::cout
	  << "Enter values in one line with whitespace as delimiter.\n"
		 "For finish entering values press Enter\n"
		 "And Ctrl+d for start statistic calculation." << std::endl;

  std::signal(SIGHUP, handler);
  const size_t statistics_count = 3;
  IStatistics *statistics[statistics_count];
  Min min{};
  Max max{};
  Mean mean{};

  statistics[0] = &min;
  statistics[1] = &max;
  statistics[2] = &mean;

  double val = 0;
  while (std::cin >> val && !std::cin.eof()) {
	for (auto &statistic : statistics) {
	  statistic->update(val);
	}
  }

// Handle invalid input data
  if (!std::cin.eof() && !std::cin.good()) {
	std::cerr << "Invalid input data\n";
	return 1;
  }

// Print results if any
  for (auto &statistic : statistics) {
	std::cout << statistic->name() << " = " << statistic->eval() << std::endl;
  }

  return 0;
}
