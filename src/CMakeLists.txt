option (DOUBLE_FFT
       "Enable double precision fourier transform code - not recommended" ON)
option (ENABLE_OSC
       "Enable Open Sound Control interface" ON)


# find libraries
find_package (PkgConfig)

pkg_check_modules (JACK REQUIRED jack>=0.80.0)
pkg_check_modules (XML REQUIRED libxml-2.0>=2.0)
pkg_check_modules (GTK REQUIRED gtk+-3.0>=3.3.10)

if (DOUBLE_FFT)
    pkg_check_modules (FFTW REQUIRED fftw3f>=3.0)
endif (DOUBLE_FFT)

if (ENABLE_OSC)
    pkg_check_modules (OSC REQUIRED liblo>=0.5)
endif (ENABLE_OSC)

## check for libm and libmx (OS X)
find_library (M_LIB m)
find_library (MX_LIB mx)
## check for libpthread and libdl
find_library (DL_LIB dl)
find_library (PTHREAD_LIB pthread)

# config
set (PACKAGE ${PROJECT_NAME})
set (HAS_OSC OSC_FOUND)
## dirs
set (PACKAGE_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share")
set (PACKAGE_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")


configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/src/config.h"
)


link_directories (
    ${JACK_LIBRARY_DIRS}
    ${FFTW_LIBRARY_DIRS}
    ${XML_LIBRARY_DIRS}
    ${GTK_LIBRARY_DIRS}
    ${OSC_LIBRARY_DIRS}
)
include_directories (
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_BINARY_DIR}/src"
    ${JACK_INCLUDE_DIRS}
    ${FFTW_INCLUDE_DRIS}
    ${XML_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
    ${OSC_INCLUDE_DIRS}
)


add_executable (g3jamin
    callbacks.c callbacks.h callbacks_help.h
    compressor.h
    compressor-ui.c compressor-ui.h
    constants.h
    db.h
    debug.h
    ladspa.h
    geq.c geq.h
    gtkmeter.c gtkmeter.h
    interface.c interface.h
    hdeq.c hdeq.h
    intrim.c intrim.h
    io.c io.h
    io-menu.c io-menu.h
    jackstatus.h
    limiter.h
    limiter-ui.c limiter-ui.h
    presets-ui.c presets-ui.h
    main.c main.h
    multiout-ui.c multiout-ui.h
    plugin.c plugin.h
    process.c process.h
    resource.c resource.h
    ringbuffer.c ringbuffer.h
    rms.c rms.h
    spectrum.c spectrum.h
    spline.c
    state.c state.h
    status-ui.c status-ui.h
    stereo.c stereo.h
    support.c support.h
    transport.c transport.h
    scenes.c scenes.h
    preferences.c preferences.h
    help.c help.h
    denormal-kill.h
    biquad.h
)
target_link_libraries (g3jamin
    ${JACK_LIBRARIES}
    ${FFTW_LIBRARIES}
    ${XML_LIBRARIES}
    ${GTK_LIBRARIES}
    ${OSC_LIBRARIES}
    ${PTHREAD_LIB}
    ${DL_LIB}
#    ${MX_LIB} TODO: check if OS X if yes include MX_LIB
    ${M_LIB}
)

add_executable (g3jamin-scene
    jamin-scene.c constants.h)
target_link_libraries (g3jamin-scene
    ${OSC_LIBRARIES}
)
