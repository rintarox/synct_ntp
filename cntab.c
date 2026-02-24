#include <stdio.h>
#include <string.h>
#include "config.h"
#include "libntpq.h"

#define CTL_OP_READSTAT 1	// ntp_control.h 

int main() {
	char assocbuf[1024];
	unsigned short assocs[MAXASSOC];
	int alen;
	int num_assocs;

	if (ntpq_openhost("localhost", AF_INET) != 1) {
		fprintf(stderr, "Ошибка открытия хоста\n");
	}

	ntpq_get_assocs();

	alen = ntpq_queryhost(CTL_OP_READSTAT, 0, assocbuf, sizeof(assocbuf)); // можно ли опкодом вытащить

	num_assocs = ntpq_read_associations(assocs, MAXASSOC);

	printf("%-5s | %-15s | %-5s | %-5s | %-10s\n", "assid", "ip", "status", "reach", "condition");
	printf("---------------------------------------------\n");

	for (int i = 0; i < num_assocs; i++) {

		const unsigned short *pus = (const unsigned short *)(assocbuf + i * 4);
		associd_t associd = ntohs(pus[0]);
		long status = ntohs(pus[1]);

		int sel = (status >> 8) & 0x07;
		const char *cond;
		switch (sel) {
			case 0: 
				cond = "reject"; 
				break;
			case 1: 
				cond = "falsetick"; 
				break;
			case 2: 
				cond = "excess"; 
				break;
			case 3: 
				cond = "outlier"; 
				break;
			case 4: 
				cond = "candidate"; 
				break;
			case 5: 
				cond = "selected"; 
				break;
			case 6: 
				cond = "sys.peer"; 
				break;
			case 7: 
				cond = "pps.peer"; 
				break;
			default: 
				cond = "unknown"; 
				break;
		}

		char peerbuf[NTPQ_BUFLEN];
		ntpq_read_assoc_peervars(associd, peerbuf, sizeof(peerbuf));
		ntpq_get_assoc_peervars(associd);

		unsigned char ipbuf[LENHOSTNAME];
		memset(ipbuf, 0, 256);
		ntpq_get_peervar("srcadr", ipbuf, sizeof(ipbuf));

		unsigned char reach[8];
		memset(reach, 0, 8);
		ntpq_get_peervar("reach", reach, sizeof(reach));
		

		printf("%-5hu | %-15s | %-6hd | %-5s | %-10s\n", associd, ipbuf, *pus, reach, cond);
	}

	ntpq_closehost();
	return 0;
}
