/// @file
/// @brief Waste memory.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: AGPL-3.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 0.1.0
/// @date 2025-03-01

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

#include "error.h"

/// @brief Print usage and exit
/// @param exit_status Exit status
/// @param progname Program name
void
usage(int exit_status, const char *progname)
{
    fprintf(
        exit_status ? stderr : stdout, "Usage: %s SIZE [SECONDS]\n", progname
    );
    exit(exit_status);
}

/// @brief Allocate memory and sleep
/// @param argc Number of arguments
/// @param argv[1] Size of memory to allocate
/// @param argv[2] Seconds to sleep(default 60)
/// @return @see sysexits.h
int
main(int argc, char *argv[])
{
    if (argc < 2) {
        usage(EX_USAGE, argv[0]);
    }
    char *endptr;
    unsigned long long size = strtoull(argv[1], &endptr, 0);
    unsigned long seconds = (argc >= 3) ? strtoul(argv[2], &endptr, 10) : 60;
    WARNX("malloc(%llu)", size);
    char *p = malloc(size);
    if (p == NULL) {
        ERR(EX_OSERR, "Failed to malloc()");
    }
    WARNX("Allocated %p", p);
    for (unsigned long long u = 0; u < size; u += 1023) {
        p[u] = u;
    }
    WARNX("sleep(%lu)", seconds);
    if (sleep(seconds)) {
        ERR(EX_UNAVAILABLE, "Woke up");
    }
    WARNX("Done");
    free(p);
    exit(EX_OK);
}
