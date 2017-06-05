CXX=g++-5
TEST_BIN=travis_test
COV_BIN=travis_test_coverage
COVFLAGS=-fprofile-arcs -ftest-coverage --coverage -fno-inline -fno-inline-small-functions -fno-default-inline
SRC=main.cpp catch.cpp
HEADERS=../TestClass.h
STD=-std=c++11
WARN=-Wall -Wextra -pedantic
OPTI=-O0 -g

all: test codecoverage cppcheck valgrind

$(TEST_BIN): $(SRC) $(HEADERS)
	$(CXX) -I.. $(OPTI) $(WARN) $(STD) -o $(TEST_BIN) $(SRC)

$(COV_BIN): $(SRC) $(HEADERS)
	$(CXX) -I.. $(OPTI) $(WARN) $(STD) -o $(COV_BIN) $(COVFLAGS) $(SRC)

test_results.xml: $(TEST_BIN)
	./$(TEST_BIN) -o test_results.xml -r junit

test: test_results.xml

coverage.baseline:
	lcov -c -i -d . -o coverage.baseline
	lcov --remove coverage.baseline '/usr/*' --output-file coverage.baseline
	lcov --remove coverage.baseline 'catch.*' --output-file coverage.baseline

codecoverage.run:
	./$(COV_BIN) > /dev/null

coverage.info:
	lcov -c -d . -o coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	lcov --remove coverage.info 'catch.*' --output-file coverage.info

coverage.combined:
	lcov -a coverage.baseline -a coverage.info -o coverage.combined

codecoverage: $(COV_BIN) coverage.baseline codecoverage.run coverage.info coverage.combined
	genhtml coverage.combined -o coverage_report

cppcheck: cppcheck.html

cppcheck.raw:
	cppcheck . -I.. --suppress='*:catch.*' --suppress='*:main.cpp' -icatch.cpp --enable=all --suppress=missingIncludeSystem --force

cppcheck.xml: $(SRC) $(HEADERS)
	cppcheck --xml --xml-version=2 --force . -I.. --suppress='*:catch.*' --suppress='*:main.cpp' -icatch.cpp --enable=all --suppress=missingIncludeSystem 2> cppcheck.xml

cppcheck.html: cppcheck_report/index.html
	cppcheck-htmlreport --source-dir=. --file=cppcheck.xml --report-dir=cppcheck_report

cppcheck_report/index.html: cppcheck.xml 
	cppcheck-htmlreport --source-dir=. --file=cppcheck.xml --report-dir=cppcheck_report

valgrind.report: $(TEST_BIN)
	valgrind --leak-check=full --show-leak-kinds=all --log-file="valgrind.report" ./$(TEST_BIN)

valgrind: valgrind.report

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f travis_test
	rm -f travis_test_coverage
	rm -f valgrind.report
	rm -f coverage.info
	rm -f cppcheck.xml
	rm -f test_results.xml
	rm -f coverage.baseline
	rm -f coverage.combined
	rm -rf cppcheck_report
	rm -rf coverage_report