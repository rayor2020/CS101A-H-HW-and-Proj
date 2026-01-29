CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic
CPPFLAGS := -I ./student
BUILD := build

.PHONY: all clean public public_ref grader grader_ref
all: public

$(BUILD):
	@mkdir -p $(BUILD)

public: $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/public_test.cpp -o $(BUILD)/public_test

clean:
	rm -rf $(BUILD)
