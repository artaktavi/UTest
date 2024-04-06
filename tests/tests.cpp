#include <AssertTests.hpp>

int main() {
  const auto start = std::chrono::high_resolution_clock::now();
  std::cout << "-------------- Tests starting ---------------\n\n";
  UTest::ToggleOStream();
  AssertTests();
  const auto stop = std::chrono::high_resolution_clock::now();
  std::cout << "\n------------- All tests passed. -------------\n";
  std::chrono::duration<double> tests_execution_time = stop - start;
  std::cout << "----- Tests execution time: " << tests_execution_time.count()
            << "s ----" << std::endl;
  return 0;
}