#include "munit/munit.h"
#include "test_common.h"

static
const MunitSuite test_suite = {
    "suite",
    test_common_suite_tests,
    NULL, //suites
    1, //iterations,
    MUNIT_SUITE_OPTION_NONE // options
};

int main(int argc, char * argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main( & test_suite, (void * )
        "µnit", argc, argv);
}