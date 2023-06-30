cmake_minimum_required(VERSION 3.11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(SetGitVersion)

project(vaccelrt
	VERSION ${VACCELRT_VERSION_BASE}
	DESCRIPTION "VaccelRT library"
	LANGUAGES C CXX)

# Configuration time options
option(BUILD_PLUGIN_EXEC "Build the exec plugin" OFF)
option(BUILD_PLUGIN_NOOP "Build the no-op debugging plugin" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(ENABLE_TESTS "Enable testing" OFF)

# Export json with compile commands
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

# installation paths
include(GNUInstallDirs)

# Add CMake third-party dependencies to be built
add_subdirectory(third-party)

# Add include directories from third-party libraries
include_directories(
	#slog
	third-party/slog/src
)

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(python)

if (BUILD_EXAMPLES)
	add_subdirectory(examples)
endif (BUILD_EXAMPLES)

# tests
if (ENABLE_TESTS)
	## Download GoogleTest framework
	configure_file(
		CMakeLists.txt.in
		googletest-download/CMakeLists.txt)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
	execute_process(
		COMMAND ${CMAKE_COMMAND} --build .
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

	# Add GTest directly to our build. This adds the targets:
	# gtest, gtest_main, gmock, and gmock_main
	add_subdirectory(
		${CMAKE_BINARY_DIR}/googletest-src
		${CMAKE_BINARY_DIR}/googletest-build)

	enable_testing()
	add_subdirectory(test)
endif (ENABLE_TESTS)

set(CPACK_PACKAGE_NAME vaccel)
set(CPACK_PACKAGE_CONTACT "Anastassios Nanos <ananos@nubificus.co.uk>")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})


include(CPack)

install(
	EXPORT vAccelTargets
	FILE vaccel-targets.cmake
	DESTINATION "${CMAKE_INSTALL_DATADIR}"
	#	NAMESPACE YourLibrary::
)

set(INCLUDE_INSTALL_DIR include)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	vaccel-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/vaccel-config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/vaccel/cmake"
	PATH_VARS INCLUDE_INSTALL_DIR)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/vaccel-config-version.cmake"
	VERSION ${CMAKE_PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/vaccel-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/vaccel-config-version.cmake"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/vaccel/cmake"
)
