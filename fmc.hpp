#ifndef FMC_HPP
#define FMC_HPP


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

#endif /* FMC_HPP */
