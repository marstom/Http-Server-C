#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "munit/munit.h"

#include "../src/common.h"

static MunitResult
test_bin2hex(const MunitParameter params[], void * data) {

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {
        "/test_bin2hex",
        test_bin2hex,
        NULL, // setup
        NULL, //tear down
        MUNIT_TEST_OPTION_NONE, // options
        NULL // params
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    }
};

static
const MunitSuite test_suite = {
    "common",
    test_suite_tests,
    NULL, //suites
    1, //iterations,
    MUNIT_SUITE_OPTION_NONE // options
};

int main(int argc, char * argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main( & test_suite, (void * )
        "µnit", argc, argv);
}