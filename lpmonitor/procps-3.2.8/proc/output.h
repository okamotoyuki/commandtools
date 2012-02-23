// using for logpool

#include <lpmonitor.h>

#define MAX_PREFIX_LEN 32

extern lpmonitor_t *lmt;
extern char prefix[MAX_PREFIX_LEN];

extern int set_prefix(char *arg);
extern void set_ip(void);

#define L_RECORD(...) do { \
	lpmonitor_record(lmt, __VA_ARGS__); \
} while(0)
