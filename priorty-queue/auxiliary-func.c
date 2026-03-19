#include <stdio.h>
#include "priority-queue.h"

void swap(u64 *a, u64 *b)
{
    u64 c = *a; *a = *b; *b = c;
}