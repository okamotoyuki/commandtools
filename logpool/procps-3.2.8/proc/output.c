// using for logpool

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "output.h"

ltrace_t *ltrace;

//extern logapi_t STRING_API;
//static void *STRING_API_PARAM[] = {(void *) 1024};

extern logapi_t SYSLOG_API;
static void *SYSLOG_API_PARAM[] = {(void *) 1024};   // using for logpool

#define FILE_API FILE2_API
extern logapi_t FILE_API;
static void *FILE_API_PARAM[] = {(void *) 1024, (void *) "LOG"};

extern logapi_t MEMCACHE_API;
static void *MEMCACHE_API_PARAM[] = {
	(void *) 1024,
	(void *) "localhost",
	(void *) 11211L
};

char prefix[MAX_PREFIX_LEN];

#define MAX_PID_LEN 5
#define MAX_HOSTNAME_LEN 26   // MAX_PREFIX_LEN - MAX_PID_LEN - 1

static void make_prefix(void) {
	char *env;

	if((env = getenv("LOGPOOL_PREFIX")) != NULL) {
		memcpy(prefix, env, strlen(env));
		return;
	}

	char hostname[MAX_HOSTNAME_LEN];
	int pid = (int)getpid();
	gethostname(hostname, MAX_HOSTNAME_LEN);
	snprintf(prefix, MAX_PREFIX_LEN, "%s+%d", hostname, pid);
	return;
}

int configure_output(char *arg) {   // using for logpool
	static int prefix_flag = 1;

	logpool_init(LOGPOOL_DEFAULT);

	if(arg == NULL) {
		if(ltrace == NULL) ltrace = ltrace_open(NULL, &SYSLOG_API, SYSLOG_API_PARAM);
		if(prefix_flag) make_prefix();
		prefix_flag = 0;
	}
	else {
		char log_syslog = "-log=syslog";
		char log_file[] = "-log=file";
		char log_memcached[] = "-log=memcached";
		char opt_prefix[] = "-prefix=";

		if(strncmp(arg, log_syslog, strlen(log_syslog)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &SYSLOG_API, SYSLOG_API_PARAM);
		}
		else if(strncmp(arg, log_file, strlen(log_file)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &FILE_API, FILE_API_PARAM);
		}
		else if(strncmp(arg, log_memcached, strlen(log_memcached)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &MEMCACHE_API, MEMCACHE_API_PARAM);
		}
		else if(strncmp(arg, opt_prefix, strlen(opt_prefix)) == 0) {
			arg += 8;
			if(prefix_flag) memcpy(prefix, arg, strlen(arg));
			prefix_flag = 0;
		}
		else {
			return 1;
		}
	}
	return 0;
}
