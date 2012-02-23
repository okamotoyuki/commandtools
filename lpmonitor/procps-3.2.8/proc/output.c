// using for logpool

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "output.h"

lpmonitor_t *lmt;

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

static char *get_server_ip(void) {
	char *ip;
	ip = getenv("LOGPOOL_SERVER_IP");
	return ip;
}

#define OPT_PREFIX_LEN 8

int set_prefix(char *arg) {
	static int prefix_flag = 1;
	if(arg == NULL) {
		if(prefix_flag) make_prefix();
		prefix_flag = 0;
	}
	else {
		char opt_prefix[] = "-prefix=";
		if(strncmp(arg, opt_prefix, OPT_PREFIX_LEN) == 0) {
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

void set_ip(void)
{
	lpmonitor_init(LOGPOOL_DEFAULT);
	char *ip = get_server_ip();
	char *host;
	int port;
	if(ip != NULL) {
		host = strtok(ip, ":");
		port = atoi(strtok(NULL, ":"));
	}
	else {
		host = "localhost";
		port = 11211;
	}
	lmt = lpmonitor_open(host, port, prefix);
}
