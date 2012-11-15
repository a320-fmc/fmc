#include <sys/time.h>

#include "fmc_window.hpp"

int main(int argc, char * argv[])
{
	struct timeval tv, tv2;

	bcm_host_init();
	fmc_window_t w(0,0,500,500);

	int i = 0;
	long long msec;
	gettimeofday(&tv, NULL);

	while(1)
	{
		if (i++ == 9) {
			gettimeofday(&tv2, NULL);
			msec = tv2.tv_sec * 1000 + tv2.tv_usec / 1000;
			msec -= tv.tv_sec * 1000 + tv.tv_usec / 1000;

			printf("%f FPS, %d msec\n", 10000.f/msec, msec);
			i = 0;
			tv = tv2;
		}
		w.render();
	}
	return 0;
}


