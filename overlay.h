
#include "cips.h"


void non_zero_overlay(sint16_t **the_image, sint16_t **out_image, sint32_t rows, sint32_t cols);

void zero_overlay(sint16_t **the_image, sint16_t **out_image, sint32_t rows, sint32_t cols);

void greater_overlay(sint16_t **the_image, sint16_t **out_image, sint32_t rows, sint32_t cols);

void less_overlay(sint16_t **the_image, sint16_t **out_image, sint32_t rows, sint32_t cols);

void average_overlay(sint16_t **the_image, sint16_t **out_image, sint32_t rows, sint32_t cols);
