// using for logpool

#include <logpool.h>

#define LOG_END 0
#define LOG_s   1
#define LOG_u   2

#define KEYVALUE_u(K,V)    LOG_u, (K), ((uintptr_t)V)

extern logpool_t *lp;
extern void *lp_args;
extern int context;

extern int configureLogPool(char *arg);

static int getTime(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (int)(((int)t.tv_sec % 1000) * 1000 * 1000 + (int)t.tv_usec);
}

#define L_RECORD(...) \
	logpool_record(lp, &lp_args, LOG_NOTICE, "dvmstat", \
			KEYVALUE_u("time", getTime()), \
			KEYVALUE_u("context", context), \
			__VA_ARGS__);
