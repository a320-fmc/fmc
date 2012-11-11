#include "fmc_window.hpp"

int main(int argc, char * argv[])
{
	bcm_host_init();
	fmc_window_t w(0,0,500,500);
	while(1) {
		w.render();
	}
	return 0;
}


