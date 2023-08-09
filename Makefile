
all:
	cmake -B build
	cmake --build build

COVERAGE_REPORT_FILENAME	=	tests/coverage_report.txt

run_tests:
	./install_criterion.sh
	cmake -B build -DTESTING=ON
	cmake --build build
	date > $(COVERAGE_REPORT_FILENAME)
	./bin/test_parser --ascii 2>> $(COVERAGE_REPORT_FILENAME)
	gcovr --exclude tests >> $(COVERAGE_REPORT_FILENAME)
	gcovr --branch --exclude tests >> $(COVERAGE_REPORT_FILENAME)
	cat $(COVERAGE_REPORT_FILENAME)

run_coverage: run_tests
	mkdir -p coverage
	gcovr --exclude tests --html-details coverage/index.html

clean:
	rm -rf build

fclean: clean
	rm -rf bin
