CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
DEBUG_FLAGS = -g -O0

NAME = matrix

SOURCES = $(filter-out tests/%, $(wildcard *.cpp))
OBJECTS = $(SOURCES:.cpp=.o)
GCOV_OBJECTS = $(SOURCES:.cpp=.gcov.o)

TEST_DIR = tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(SOURCES:.cpp=.o) $(TEST_SOURCES:.cpp=.o)
GCOV_TEST_OBJECTS = $(SOURCES:.cpp=.gcov.o) $(TEST_SOURCES:.cpp=.gcov.o)
TEST_NAME = $(NAME)_test
GCOV_TEST_NAME = $(NAME)_test_gcov

GTEST_FLAGS = -lgtest -pthread

all: gcov_report s21_matrix_oop.a

test: $(TEST_NAME)
	./$(TEST_NAME)

gcov_report: clean $(GCOV_TEST_NAME)
	./$(GCOV_TEST_NAME)
	gcovr --root . --exclude $(TEST_DIR)/ --exclude ".*_test\.cpp" --html --html-details -o coverage_report.html
	gcovr --root . --exclude $(TEST_DIR)/ --exclude ".*_test\.cpp" --print-summary
	@echo "Отчет покрытия: coverage_report.html"

$(TEST_NAME): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $@ $^ $(GTEST_FLAGS)

$(GCOV_TEST_NAME): $(GCOV_TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(GCOV_FLAGS) -o $@ $^ $(GTEST_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

%.gcov.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(TEST_DIR)/%.gcov.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(GCOV_FLAGS) -c $< -o $@

clean:
	rm -rf $(NAME) $(TEST_NAME) $(GCOV_TEST_NAME) *.o $(TEST_DIR)/*.o *.gcov.* *.gcda *.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno coverage_report.html coverage/
	rm -rf *.gcda *.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno *.html *.css

clang:
	find . -type f \( -name "*.h" -o -name "*.cpp" \) -exec clang-format -i {} \;

valgrind: $(TEST_NAME)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_NAME)

s21_matrix_oop.a: $(OBJECTS)
	ar rcs s21_matrix_oop.a $(OBJECTS)

.PHONY: all test gcov_report clean clang valgrind s21_matrix_oop.a