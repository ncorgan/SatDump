cmake_minimum_required(VERSION 3.0.0)
project(usrp_sdr_support)

set(SATDUMP_ROOT "/usr")

# TODO: figure out min UHD version based on logging, etc
find_package(UHD)

if(UHD_FOUND)
    message("Building with USRP support")
    file(GLOB_RECURSE usrp_sdr_support_CPPS *.cpp)
    add_library(usrp_sdr_support SHARED ${usrp_sdr_support_CPPS})

    target_link_libraries(usrp_sdr_support ${UHD_LIBRARIES})

    target_include_directories(usrp_sdr_support PUBLIC
        ${UHD_INCLUDE_DIRS}
        ${SATDUMP_ROOT}/include/satdump)

    install(TARGETS usrp_sdr_support DESTINATION share/satdump/plugins)
else()
    message("UHD Library could not be found! Not building.")
endif()
