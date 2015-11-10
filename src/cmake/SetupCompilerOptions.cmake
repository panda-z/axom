############################
# Setup compiler options
############################

#############################################
# Support extra compiler flags and defines
#############################################
#
# We don't try to use this approach for CMake generators that support
# multiple configurations. See: CZ JIRA: ATK-45
#
if(NOT CMAKE_CONFIGURATION_TYPES)

    ######################################################
    # Add define we can use when debug builds are enabled
    ######################################################
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DATK_DEBUG)
    endif()

    ##########################################
    # Support Extra Flags for the C compiler.
    ##########################################
    if(EXTRA_C_FLAGS)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
    endif()

    # Extra Flags for the debug builds with the C compiler.
    if(EXTRA_C_FLAGS_DEBUG AND CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options("${EXTRA_C_FLAGS_DEBUG}")
    endif()

    # Extra Flags for the release builds with the C compiler.
    if(EXTRA_C_FLAGS_RELEASE AND CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_compile_options("${EXTRA_C_FLAGS_RELEASE}")
    endif()

    #############################################
    # Support Extra Flags for the C++ compiler.
    #############################################
    if(EXTRA_CXX_FLAGS)
        add_compile_options("${EXTRA_CXX_FLAGS}")
    endif()

    # Extra Flags for the debug builds with the C++ compiler.
    if(EXTRA_CXX_FLAGS_DEBUG AND CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options("${EXTRA_CXX_FLAGS_DEBUG}")
    endif()

    # Extra Flags for the release builds with the C++ compiler.
    if(EXTRA_CXX_FLAGS_RELEASE AND CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_compile_options("${EXTRA_CXX_FLAGS_RELEASE}")
    endif()

endif()

################################
# RPath Settings
################################

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

################################
# Compiler warnings
################################
include(EnableExtraCompilerWarnings)
if (ENABLE_GLOBALCOMPILERWARNINGS)
   globally_enable_extra_compiler_warnings()
   MESSAGE(STATUS  "Enabling extra compiler warnings on all targets.")
endif()

################################
# Compiler warnings as errors
################################
include(EnableCompilerWarningsAsErrors)
if (ENABLE_GLOBALCOMPILERWARNINGSASERRORS)
   globally_enable_compiler_warnings_as_errors()
   MESSAGE(STATUS  "Treating compiler warnings as errors on all targets.")
endif()


################################
# Enable C++11 
################################
## Enable ENABLE C++ 11 features
if (ENABLE_CXX11)
  # define a macro so the code can ifdef accordingly.
  add_definitions("-DUSE_CXX11")
endif()

################################
# Enable Fortran
################################
if(ENABLE_FORTRAN)
    add_definitions(-DATK_ENABLE_FORTRAN)

    # if enabled but no fortran compiler, halt the configure
    if(CMAKE_Fortran_COMPILER)
        MESSAGE(STATUS  "Fortran support enabled.")
    else()
        MESSAGE(FATAL_ERROR "Fortran support selected, but no Fortran compiler was found.")
    endif()

    # default property to free form
    set(CMAKE_Fortran_FORMAT FREE)

    # Create macros for Fortran name mangling
    include(FortranCInterface)
    FortranCInterface_HEADER(${HEADER_INCLUDES_DIRECTORY}/common/FC.h MACRO_NAMESPACE "FC_")
else()
    MESSAGE(STATUS  "Fortran support disabled.")
endif()
 
