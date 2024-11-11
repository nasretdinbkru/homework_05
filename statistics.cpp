#include <iostream>
#include <limits>
#include <cstring>
#include <vector>

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

//class Mean : public IStatistics {
// public:
//  Mean() : m_mean{std::numeric_limits<double>::mean()} {
//  }
//
//  void update(double next) override {
//	if (next < m_mean) {
//	  m_mean = next;
//	}
//  }
//
//  [[nodiscard]] double eval() const override {
//	return m_mean;
//  }
//
//  [[nodiscard]] const char *name() const override {
//	return "max";
//  }
//
// private:
//  double m_mean;
//};


int main() {


  const size_t statistics_count = 2;
  IStatistics *statistics[statistics_count];

  statistics[0] = new Min{};
  statistics[1] = new Max{};

  double val = 0;
  while (std::cin >> val) {
	if (val == 'E' ) break;
	if (!std::cin.good()){
	  std::cerr << "Invalid input data\n";
	  continue;
	}
	for (auto &statistic : statistics) {
	  statistic->update(val);
	}
  }

//  // Handle invalid input data
//  if (!std::cin.eof() && !std::cin.good()) {
//	std::cerr << "Invalid input data\n";
//	return 1;
//  }

  // Print results if any
  for (auto &statistic : statistics) {
	std::cout << statistic->name() << " = " << statistic->eval() << std::endl;
  }

  // Clear memory - delete all objects created by new
  for (auto &statistic : statistics) {
	delete statistic;
  }

  return 0;
}
