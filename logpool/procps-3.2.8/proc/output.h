// using for logpool

#include <logpool.h>

#define MAX_PREFIX_LEN 32

extern ltrace_t *ltrace;
extern char prefix[MAX_PREFIX_LEN];

extern int configure_output(char *arg);

#define L_RECORD(...) do { \
	ltrace_record(ltrace, prefix , __VA_ARGS__); \
} while(0)
