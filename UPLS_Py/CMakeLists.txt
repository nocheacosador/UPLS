cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)

if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()

project(UPLS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sample_library "lib_UPLS")
set(bindings_library "UPLS")

set(typesystem_file ${CMAKE_SOURCE_DIR}/bindings/bindings.xml)
set(wrapped_header	${CMAKE_SOURCE_DIR}/bindings/bindings.h)

set(shared_includes ${CMAKE_SOURCE_DIR}/../shared)
include_directories(${shared_includes})

set(generated_sources
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/command_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/hookinfo_latch_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/landinggearinfo_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/ledinfo_led_settings_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/ledinfo_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/warning_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/error_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/hookinfo_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/upls_controller_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/winchinfo_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/hookinfo_battery_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/landinggearinfo_leg_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/ledinfo_led_wrapper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/${bindings_library}/upls_module_wrapper.cpp
	)

if(NOT python_interpreter)
    find_program(python_interpreter "python3")
endif()
message(STATUS "Using python interpreter: ${python_interpreter}")

macro(pyside2_config option output_var)
    if(${ARGC} GREATER 2)
        set(is_list ${ARGV2})
    else()
        set(is_list "")
    endif()

    execute_process(
      COMMAND ${python_interpreter} "${CMAKE_SOURCE_DIR}/utils/pyside2_config.py"
              ${option}
      OUTPUT_VARIABLE ${output_var}
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    if ("${${output_var}}" STREQUAL "")
        message(FATAL_ERROR "Error: Calling pyside2_config.py ${option} returned no output.")
    endif()
    if(is_list)
        string (REPLACE " " ";" ${output_var} "${${output_var}}")
    endif()
endmacro()

# Query for the shiboken generator path, Python path, include paths and linker flags.
pyside2_config(--shiboken2-module-path shiboken2_module_path)
pyside2_config(--shiboken2-generator-path shiboken2_generator_path)
pyside2_config(--python-include-path python_include_dir)
pyside2_config(--shiboken2-generator-include-path shiboken_include_dir 1)
pyside2_config(--shiboken2-module-shared-libraries-cmake shiboken_shared_libraries 0)
pyside2_config(--python-link-flags-cmake python_linking_data 0)

set(shiboken_path "${shiboken2_generator_path}/shiboken2${CMAKE_EXECUTABLE_SUFFIX}")
if(NOT EXISTS ${shiboken_path})
    message(FATAL_ERROR "Shiboken executable not found at path: ${shiboken_path}")
endif()


# ==================================== RPATH configuration ====================================


# =============================================================================================
# !!! (The section below is deployment related, so in a real world application you will want to
# take care of this properly with some custom script or tool).
# =============================================================================================
# Enable rpaths so that the built shared libraries find their dependencies.
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${shiboken2_module_path} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# =============================== CMake target - sample_library ===============================

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# ====================== Shiboken target for generating binding C++ files  ====================

# Set up the options to pass to shiboken.
set(shiboken_options --generator-set=shiboken --enable-parent-ctor-heuristic
    --enable-return-value-heuristic --use-isnull-as-nb_nonzero
    --avoid-protected-hack -std=c++17
    -I${CMAKE_SOURCE_DIR}/bindings -I${CMAKE_SOURCE_DIR}/src -I${shared_includes}
    -T${CMAKE_SOURCE_DIR}/bindings
    --output-directory=${CMAKE_BINARY_DIR}
	)

set(generated_sources_dependencies ${wrapped_header} ${typesystem_file})

# Add custom target to run shiboken to generate the binding cpp files.
add_custom_command( OUTPUT ${generated_sources}
                    COMMAND ${shiboken_path}
                    ${shiboken_options} ${wrapped_header} ${typesystem_file}
                    DEPENDS ${generated_sources_dependencies}
                    IMPLICIT_DEPENDS CXX ${wrapped_header}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Running generator for ${typesystem_file}.")


# =============================== CMake target - bindings_library =============================

# Set the cpp files which will be used for the bindings library.
set(${bindings_library}_sources ${generated_sources})

# Define and build the bindings library.
add_library(${bindings_library} MODULE ${${bindings_library}_sources})

# Apply relevant include and link flags.
target_include_directories(${bindings_library} PRIVATE ${python_include_dir})
target_include_directories(${bindings_library} PRIVATE ${shiboken_include_dir})
target_include_directories(${bindings_library} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${bindings_library} PRIVATE ${shiboken_shared_libraries})
target_link_libraries(${bindings_library} PRIVATE ${sample_library})

# Adjust the name of generated module.
set_property(TARGET ${bindings_library} PROPERTY PREFIX "")
set_property(TARGET ${bindings_library} PROPERTY OUTPUT_NAME
             "${bindings_library}${PYTHON_EXTENSION_SUFFIX}")
if(WIN32)
    set_property(TARGET ${bindings_library} PROPERTY SUFFIX ".pyd")
endif()

# Make sure the linker doesn't complain about not finding Python symbols on macOS.
if(APPLE)
  set_target_properties(${bindings_library} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif(APPLE)

# Find and link to the python import library only on Windows.
# On Linux and macOS, the undefined symbols will get resolved by the dynamic linker
# (the symbols will be picked up in the Python executable).
if (WIN32)
    list(GET python_linking_data 0 python_libdir)
    list(GET python_linking_data 1 python_lib)
    find_library(python_link_flags ${python_lib} PATHS ${python_libdir} HINTS ${python_libdir})
    target_link_libraries(${bindings_library} PRIVATE ${python_link_flags})
endif()


# ================================= Dubious deployment section ================================

set(windows_shiboken_shared_libraries)

if(WIN32)
    # =========================================================================================
    # !!! (The section below is deployment related, so in a real world application you will
    # want to take care of this properly (this is simply to eliminate errors that users usually
    # encounter.
    # =========================================================================================
    # Circumvent some "#pragma comment(lib)"s in "include/pyconfig.h" which might force to link
    # against a wrong python shared library.

    set(python_versions_list 3 32 33 34 35 36 37 38)
    set(python_additional_link_flags "")
    foreach(ver ${python_versions_list})
        set(python_additional_link_flags
            "${python_additional_link_flags} /NODEFAULTLIB:\"python${ver}_d.lib\"")
        set(python_additional_link_flags
            "${python_additional_link_flags} /NODEFAULTLIB:\"python${ver}.lib\"")
    endforeach()

    set_target_properties(${bindings_library}
                           PROPERTIES LINK_FLAGS "${python_additional_link_flags}")

    # Compile a list of shiboken shared libraries to be installed, so that
    # the user doesn't have to set the PATH manually to point to the PySide2 package.
    foreach(library_path ${shiboken_shared_libraries})
        string(REGEX REPLACE ".lib$" ".dll" library_path ${library_path})
        file(TO_CMAKE_PATH ${library_path} library_path)
        list(APPEND windows_shiboken_shared_libraries "${library_path}")
    endforeach()
    # =========================================================================================
    # !!! End of dubious section.
    # =========================================================================================
endif()

# =============================================================================================
# Install the library and the bindings module into the source folder near the main.py file, so
# that the Python interpeter successfully imports the used module.
install(TARGETS ${bindings_library} #${sample_library}
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
        )
install(FILES ${windows_shiboken_shared_libraries} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)

install(TARGETS ${bindings_library} #${sample_library}
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../UPLS_PyDemoApp
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../UPLS_PyDemoApp
        )
install(FILES ${windows_shiboken_shared_libraries} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../UPLS_PyDemoApp)
