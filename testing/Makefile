CXX=g++-5
TEST_BIN=travis_test
COV_BIN=travis_test_coverage
COVFLAGS=-fprofile-arcs -ftest-coverage -fPIC --coverage -fno-inline -fno-inline-small-functions -fno-default-inline
SRC=main.cpp catch.cpp
HEADERS=../TestClass.h
STD=-std=c++11
WARN=-Wall -Wextra -pedantic
OPTI=-O0 -g

.PHONY: test test_results.xml cppcheck.xml cppcheck.html valgrind valgrind.report valgrind.xml coverage coverage.gcovr

all: test coverage cppcheck valgrind

$(TEST_BIN): $(SRC) $(HEADERS)
	$(CXX) -I.. $(OPTI) $(WARN) $(STD) -o $(TEST_BIN) $(SRC)

$(COV_BIN): $(SRC) $(HEADERS)
	$(CXX) -I.. $(OPTI) $(WARN) $(STD) -o $(COV_BIN) $(COVFLAGS) $(SRC) 2> /dev/null

test_results.xml: $(TEST_BIN)
	./$(TEST_BIN) -o test_results.xml -r junit

test: test_results.xml

coverage.baseline: $(COV_BIN)
	lcov -c -i -d . -o $@
	lcov --remove $@ '/usr/*' --output-file $@
	lcov --remove $@ 'catch.*' --output-file $@
	lcov --remove $@ 'testing/*' --output-file $@

coverage.run: coverage.baseline
	./$(COV_BIN) > /dev/null

coverage.info: coverage.run
	lcov -c -d . -o $@
	lcov --remove $@ '/usr/*' --output-file $@
	lcov --remove $@ 'catch.*' --output-file $@
	lcov --remove $@ 'testing/*' --output-file $@

coverage.combined: coverage.info
	lcov -a coverage.baseline -a coverage.info -o $@

coverage.lcov: coverage.combined
	genhtml coverage.combined -o coverage_report

coverage.gcovr:
	gcovr -e catch.hpp -e main.cpp --branches --xml-pretty -r . > coverage.xml

coverage.gcovr.html:
	gcovr -e catch.hpp -e main.cpp --branches --html -r . -o coverage.html

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
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=no --undef-value-errors=yes --track-origins=yes --child-silent-after-fork=no --trace-children=no --gen-suppressions=no --log-file="valgrind.report" ./$(TEST_BIN)

valgrind.xml: $(TEST_BIN)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=no --undef-value-errors=yes --track-origins=yes --child-silent-after-fork=no --trace-children=no --gen-suppressions=no --xml=yes --xml-file=valgrind.xml $(TEST_BIN)

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
	rm -f coverage.html
	rm -f coverage.xml
	rm -f valgrind.xml
	rm -f coverage.baseline
	rm -f coverage.combined
	rm -rf cppcheck_report
	rm -rf coverage_report