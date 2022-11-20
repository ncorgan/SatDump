cmake_minimum_required(VERSION 3.0.0)
project(soapysdr_sdr_support)

set(SATDUMP_ROOT "/usr")

find_package(SoapySDR)

if(SoapySDR_FOUND)
    message("Building with SoapySDR support")
    file(GLOB_RECURSE soapysdr_sdr_support_CPPS *.cpp)
    add_library(soapysdr_sdr_support SHARED ${soapysdr_sdr_support_CPPS})

    # TODO: recreate SatDump's per-platform links
    target_link_libraries(soapysdr_sdr_support
        SoapySDR
        volk)

    # TODO: recreate SatDump's per-platform includes
    target_include_directories(soapysdr_sdr_support PUBLIC
        ${SATDUMP_ROOT}/include/satdump
        ${volk_INCLUDE_DIRS})

    install(TARGETS soapysdr_sdr_support DESTINATION share/satdump/plugins)
else()
    message("SoapySDR Library could not be found! Not building.")
endif()
