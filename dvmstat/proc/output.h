// using for logpool

#include <logpool.h>

#define LOG_END 0
#define LOG_s   1
#define LOG_u   2

#define KEYVALUE_u(K,V)    LOG_u, (K), ((uintptr_t)V)
#define KEYVALUE_s(K,V)    LOG_s, (K), (V)

extern logpool_t *lp;
extern void *lp_args;
extern int context;

extern int configureLogPool(char *arg);

#define L_RECORD(...) \
	logpool_record(lp, &lp_args, LOG_NOTICE, "dvmstat", \
			__VA_ARGS__);

//	KEYVALUE_s("context", context), \
