#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "munit/munit.h"

#include "../src/common.h"

static MunitResult
test_bin2hex(const MunitParameter params[], void * data) {
    char *out = bin2hex("Tomek", 5);
    printf("\n%s\n", out);
    munit_assert_string_equal(out, "54 6F 6D 65 6B ");
    return MUNIT_OK;
}

static MunitResult
test_err_n_die(const MunitParameter params[], void * data) {

    return MUNIT_OK;
}



int)
// all tests list for this module here
static MunitTest test_common_suite_tests[] = {
    {
        "/test_bin2hex",
        test_bin2hex,
        NULL, // setup
        NULL, //tear down
        MUNIT_TEST_OPTION_NONE, // options
        NULL // params
    },
    {
        "/test_err_n_die",
        test_err_n_die,
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



