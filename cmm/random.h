#pragma once

#include <stdlib.h>

/// Sample valuie from uniform random distribution in range [0; 1]
#define RANDOM_UNIFORM(type) ((type)rand() / RAND_MAX)
