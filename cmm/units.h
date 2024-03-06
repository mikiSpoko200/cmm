#pragma once

#include "common.h"

#define KiB(N) ((N) * 1024)
#define MiB(N) (KiB(N) * 1024)
#define GiB(N) (MiB(N) * 1024)

#define KB(N) ((N) / 1000)
#define MB(N) (KB(N) / 1000)
#define GB(N) (MB(N) / 1000)
