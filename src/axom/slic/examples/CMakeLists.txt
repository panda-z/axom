# Copyright (c) 2017-2021, Lawrence Livermore National Security, LLC and
# other Axom Project Developers. See the top-level COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
#------------------------------------------------------------------------------
# Examples for Slic component
#------------------------------------------------------------------------------

set(example_sources
    basic/cpplogger.cpp
    basic/custom_abort_logger.cpp
    basic/logging.cpp
    multicode/driver.cpp
    )

set(mpi_example_sources
    basic/parallel_logging.cpp
    basic/separate_file_per_rank.cpp
    )

if (AXOM_ENABLE_LUMBERJACK)
    list(APPEND mpi_example_sources basic/lumberjack_logging.cpp )
endif()

foreach( example_source ${example_sources} )
    get_filename_component( example_name ${example_source} NAME_WE )
    blt_add_executable( NAME       slic_${example_name}_ex
                        SOURCES    ${example_source} 
                        DEPENDS_ON slic
                        OUTPUT_DIR ${EXAMPLE_OUTPUT_DIRECTORY}
                        FOLDER     axom/slic/examples )

    if(AXOM_ENABLE_TESTS)
        axom_add_test( NAME   slic_${example_name}
                      COMMAND slic_${example_name}_ex )
    endif()
endforeach()


if ( ENABLE_MPI )
    foreach( example_source ${mpi_example_sources} )
        get_filename_component( example_name ${example_source} NAME_WE )
        blt_add_executable( NAME       slic_mpi_${example_name}_ex
                            SOURCES    ${example_source}
                            OUTPUT_DIR ${EXAMPLE_OUTPUT_DIRECTORY}
                            DEPENDS_ON slic 
                            FOLDER     axom/slic/examples )

        if(AXOM_ENABLE_TESTS)
            axom_add_test( NAME    slic_mpi_${example_name}
                           COMMAND slic_mpi_${example_name}_ex
                           NUM_MPI_TASKS 4)
        endif()
    endforeach()
endif()
