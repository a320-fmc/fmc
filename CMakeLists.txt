cmake_minimum_required (VERSION 2.6) 
 
set (PROJECT pi_fmc) 
 
project (${PROJECT}) 
 
set (HEADERS 
	window.hpp
	fmc_window.hpp)
 
set (SOURCES 
	window.cpp
	path.cpp
	fmc_window.cpp
	horizon.cpp
	main.cpp)
 
include_directories("/opt/vc/include"
			"/opt/vc/include/interface/vcos/pthreads")

link_directories("/opt/vc/lib")

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT}
			GLESv2
			EGL
			openmaxil
			bcm_host
			vcos
			vchiq_arm)


