#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

#include <stdlib.h>
#include <string>
#include <vector>

#define TEST_CASE(name) { #name, name }

typedef bool (*FuncPointer) ();

typedef struct TestInfo {
    std::string description;
    FuncPointer func_ptr;
} TestInfo;

typedef struct TestSuite {
    std::string name;
    std::vector<TestInfo> tests;
} TestSuite;

typedef struct TestSuiteResult {
    size_t passed_count;
} TestSuiteResult;

void run_test_suites(const std::vector<TestSuite>& test_suites);

#endif //_TEST_RUNNER_H_
