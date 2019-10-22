#include <check.h>
#include "../include/bitarray.h"

START_TEST(write_position) {

    BitArray *bitArray = bitarray_create(150);

    bitarray_writeBit(bitArray, 12, 1);

    fail_unless(bitarray_valueOf(bitArray, 12) == 1);
    fail_unless(bitarray_valueOf(bitArray, 0) == 0);

}
END_TEST

START_TEST(write_position_beyond_bound_of_int) {

    BitArray *bitArray = bitarray_create(1024);

    bitarray_writeBit(bitArray, 429, 1);

    fail_unless(bitarray_valueOf(bitArray, 429) == 1);
    fail_unless(bitarray_valueOf(bitArray, 144) == 0, "Value at 144 should be 0 but was %d", bitarray_valueOf(bitArray, 144));

}
END_TEST

START_TEST(write_same_position_twice) {

    BitArray *bitArray = bitarray_create(1024);

    bitarray_writeBit(bitArray, 429, 1);
    bitarray_writeBit(bitArray, 429, 1);
    bitarray_writeBit(bitArray, 430, 1);

    fail_unless(bitarray_valueOf(bitArray, 429) == 1);
    fail_unless(bitarray_valueOf(bitArray, 430) == 1);
    fail_unless(bitarray_valueOf(bitArray, 144) == 0, "Value at 144 should be 0 but was %d", bitarray_valueOf(bitArray, 144));

}
END_TEST

void bitarray_tests_addToSuite(Suite *suite) {
    TCase *bitarrayTests = tcase_create("Bit Array Tests");

    tcase_add_test(bitarrayTests, write_position);
    tcase_add_test(bitarrayTests, write_position_beyond_bound_of_int);
    tcase_add_test(bitarrayTests, write_same_position_twice);

    suite_add_tcase(suite, bitarrayTests);

}