#!/usr/bin/env bash
# Master test script - runs all cub3d tests
# Executes all test suites and provides a comprehensive summary

MASTER_RESULTS="master_test_results"

# Remove old master results and create fresh one
rm -f "$MASTER_RESULTS"
touch "$MASTER_RESULTS"

# Color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

printf "${BLUE}==========================================================\n"
printf "           CUB3D COMPREHENSIVE TEST SUITE\n"
printf "==========================================================\n${NC}\n"
printf "Starting at: %s\n\n" "$(date)" | tee -a "$MASTER_RESULTS"

# Counter for passed/failed tests
total_suites=4
passed_suites=0

# Test 1: Good Maps Execution
printf "${YELLOW}[1/4] Running Good Maps Test...${NC}\n"
printf "\n=== TEST 1: GOOD MAPS EXECUTION ===\n" >> "$MASTER_RESULTS"
bash run_good_maps.sh
test1_result=$?
if [ $test1_result -eq 0 ]; then
    printf "${GREEN}✓ Good Maps Test: PASSED${NC}\n\n"
    printf "Status: PASSED\n\n" >> "$MASTER_RESULTS"
    passed_suites=$((passed_suites+1))
else
    printf "${RED}✗ Good Maps Test: FAILED${NC}\n\n"
    printf "Status: FAILED\n\n" >> "$MASTER_RESULTS"
fi
cat results >> "$MASTER_RESULTS"
printf "\n---\n\n" >> "$MASTER_RESULTS"

# Test 2: Bad Maps Execution
printf "${YELLOW}[2/4] Running Bad Maps Test...${NC}\n"
printf "=== TEST 2: BAD MAPS EXECUTION ===\n" >> "$MASTER_RESULTS"
bash run_bad_maps.sh
test2_result=$?
if [ $test2_result -eq 0 ]; then
    printf "${GREEN}✓ Bad Maps Test: PASSED${NC}\n\n"
    printf "Status: PASSED\n\n" >> "$MASTER_RESULTS"
    passed_suites=$((passed_suites+1))
else
    printf "${RED}✗ Bad Maps Test: FAILED${NC}\n\n"
    printf "Status: FAILED\n\n" >> "$MASTER_RESULTS"
fi
cat results >> "$MASTER_RESULTS"
printf "\n---\n\n" >> "$MASTER_RESULTS"

# Test 3: Good Maps Leak Check
printf "${YELLOW}[3/4] Running Good Maps Leak Check...${NC}\n"
printf "=== TEST 3: GOOD MAPS LEAK CHECK ===\n" >> "$MASTER_RESULTS"
bash check_leaks_good.sh
# Leak checks don't return exit codes, check if successful message is in results
if grep -q "TEST SUCCESSFUL" results_leaks_good; then
    printf "${GREEN}✓ Good Maps Leak Check: PASSED${NC}\n\n"
    printf "Status: PASSED\n\n" >> "$MASTER_RESULTS"
    passed_suites=$((passed_suites+1))
else
    printf "${RED}✗ Good Maps Leak Check: FAILED${NC}\n\n"
    printf "Status: FAILED\n\n" >> "$MASTER_RESULTS"
fi
cat results_leaks_good >> "$MASTER_RESULTS"
printf "\n---\n\n" >> "$MASTER_RESULTS"

# Test 4: Bad Maps Leak Check
printf "${YELLOW}[4/4] Running Bad Maps Leak Check...${NC}\n"
printf "=== TEST 4: BAD MAPS LEAK CHECK ===\n" >> "$MASTER_RESULTS"
bash check_leaks_bad.sh
# Leak checks don't return exit codes, check if successful message is in results
if grep -q "TEST SUCCESSFUL" results_leaks_bad; then
    printf "${GREEN}✓ Bad Maps Leak Check: PASSED${NC}\n\n"
    printf "Status: PASSED\n\n" >> "$MASTER_RESULTS"
    passed_suites=$((passed_suites+1))
else
    printf "${RED}✗ Bad Maps Leak Check: FAILED${NC}\n\n"
    printf "Status: FAILED\n\n" >> "$MASTER_RESULTS"
fi
cat results_leaks_bad >> "$MASTER_RESULTS"
printf "\n---\n\n" >> "$MASTER_RESULTS"

# Final Summary
printf "${BLUE}==========================================================\n"
printf "                   FINAL SUMMARY\n"
printf "==========================================================\n${NC}\n"

printf "\n==========================================================\n" >> "$MASTER_RESULTS"
printf "                   FINAL SUMMARY\n" >> "$MASTER_RESULTS"
printf "==========================================================\n" >> "$MASTER_RESULTS"
printf "Completed at: %s\n" "$(date)" >> "$MASTER_RESULTS"
printf "Test Suites Passed: %d/%d\n" "$passed_suites" "$total_suites" >> "$MASTER_RESULTS"

if [ $passed_suites -eq $total_suites ]; then
    printf "${GREEN}\n🎉 ALL TESTS PASSED! (%d/%d)${NC}\n" "$passed_suites" "$total_suites"
    printf "\n✅ ALL TESTS PASSED!\n" >> "$MASTER_RESULTS"
    printf "Your cub3D is working perfectly!\n\n" | tee -a "$MASTER_RESULTS"
    exit 0
else
    printf "${RED}\n❌ SOME TESTS FAILED (%d/%d passed)${NC}\n" "$passed_suites" "$total_suites"
    printf "\n❌ SOME TESTS FAILED\n" >> "$MASTER_RESULTS"
    printf "Please check individual test results above.\n\n" | tee -a "$MASTER_RESULTS"
    exit 1
fi
