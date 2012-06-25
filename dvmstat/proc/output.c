// using for logpool

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "output.h"

logpool_t *lp;
void *lp_args;
int context = 0;

logpool_t *logpool_open_trace32(logpool_t *parent, char *host, int port)
{
	struct logpool_param_stream param = {32, 2048};
	param.host = host;
	param.port = port;
	extern struct logapi STREAM_API;
	return logpool_open(parent, &STREAM_API, (struct logpool_param*) &param);
}

#define OPT_LOGPOOL_LEN 9
#define OPT_CONTEXT_LEN 9
#define MAX_LOGPOOLIP_LEN 32

int configureLogPool(char *arg) {
	char opt_logpool[] = "-logpool=";
	char opt_context[] = "-context=";
	char logpoolip[MAX_LOGPOOLIP_LEN];

	if(arg == NULL) {
		if(!lp) lp = logpool_open_trace32(NULL, "0.0.0.0", 14801);
		return 0;
	}
	else {
		if(strncmp(arg, opt_logpool, OPT_LOGPOOL_LEN) == 0) {
			arg += OPT_LOGPOOL_LEN;
			strncpy(logpoolip, arg, strlen(arg) + 1);
			if(!lp) lp = logpool_open_trace32(NULL, logpoolip, 14801);
			return 0;
		}
		else if(strncmp(arg, opt_context, OPT_CONTEXT_LEN) == 0) {
			arg += OPT_CONTEXT_LEN;
			context = atoi(arg);
			return 0;
		}
	}
	return 1;
}
