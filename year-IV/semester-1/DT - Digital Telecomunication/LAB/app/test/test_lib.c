#include <stdlib.h>

typedef struct _Test {
    char *name;
    void (*test)(void);
    _Test *next;
    _Test *tail;
} Test;

typedef struct _TestSuite {
    char *name;
    Test *tests;
    _TestSuite *next;
    _TestSuite *tail;
} TestSuite;

#define TEST_SUITE(name) \
    TestSuite name = { #name, NULL, NULL }

#define TEST(suite, name) \
    void test_##suite##_##name(void); \
    attribute((constructor)) void test_##suite##_##name##_constructor(void) { \
        Test *test = (Test*) malloc(sizeof(Test)); \
        test->name = #name; \
        test->test = test_##suite##_##name; \
        test->next = NULL; \
        if (suite.tests == NULL) { \
            suite.tests = test; \
            suite.tail = test; \
        } else { \
            suite.tail->next = test; \
            suite.tail = test; \
        } \
    } \
    Test test_##suite##_##name##_obj = { #name, test_##suite##_##name, NULL }; \
    void test_##suite##_##name(void)

#define TEST_SUITE_ADD(suite, test) \
    if (suite.tests == NULL) { \
        suite.tests = &test; \
    } else { \
        suite.tail->next = &test; \
    } \
    suite.tail = &test;


TEST_SUITE(RandomTests);

TEST(RandomTests, Test1) {
    printf("Test1\n");
}

int main(int argc, char *argv[]) {

    return 0;
}