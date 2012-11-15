#ifndef FMC_HPP
#define FMC_HPP

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>

static inline void check_vg_error(VGErrorCode err) {
	if (err != VG_NO_ERROR)
	{
		std::cerr << "Error: " << err << std::endl;
		std::stringstream ss;
		ss << "Error code: " << std::hex << err;
		throw std::runtime_error(ss.str().c_str());
	}
}

static inline void check_vg_error(VGUErrorCode err) {
	if (err != VGU_NO_ERROR)
	{
		std::cerr << "Error: " << err << std::endl;
		std::stringstream ss;
		ss << "Error code: " << std::hex << err;
		throw std::runtime_error(ss.str().c_str());
	}
}

static inline float deg_to_rad(float deg) {
	return (deg * M_PI / 180);
}

#endif /* FMC_HPP */
