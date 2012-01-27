// using for logpool

#include "output.h"

extern logapi_t STRING_API;
static void *STRING_API_PARAM[] = {(void *) 1024};

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

ltrace_t *ltrace;

void select_stdout(char *arg) {   // using for logpool
	logpool_init(LOGPOOL_DEFAULT);
	if(arg == NULL) {
		if(ltrace == NULL) ltrace = ltrace_open(NULL, &STRING_API, STRING_API_PARAM);
	}
	else {
		char opt_syslog[] = "-stdout=syslog";
		char opt_file[] = "-stdout=file";
		char opt_memcached[] = "-stdout=memcached";

		if(strncmp(arg, opt_syslog, strlen(opt_syslog)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &SYSLOG_API, SYSLOG_API_PARAM);
		}
		else if(strncmp(arg, opt_file, strlen(opt_file)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &FILE_API, FILE_API_PARAM);
		}
		else if(strncmp(arg, opt_memcached, strlen(opt_memcached)) == 0) {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &MEMCACHE_API, MEMCACHE_API_PARAM);
		}
		else {
			if(ltrace == NULL) ltrace = ltrace_open(NULL, &STRING_API, STRING_API_PARAM);
		}
	}
}
