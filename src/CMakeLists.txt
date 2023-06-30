# Core runtime sources
file(GLOB_RECURSE sources *.c)

# core runtime headers
file(GLOB_RECURSE headers *.h)

configure_file(${CMAKE_SOURCE_DIR}/src/include/vaccel.h.in
	${CMAKE_SOURCE_DIR}/src/include/vaccel.h @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/vaccel.h.in
	${CMAKE_SOURCE_DIR}/src/vaccel.h @ONLY)

add_library(vaccel SHARED ${headers} ${sources})
target_compile_options(vaccel PUBLIC -Wall -Wextra -Werror -pthread)
target_include_directories(vaccel PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(vaccel PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_include_directories(vaccel PRIVATE ${CMAKE_BINARY_DIR})

target_include_directories(vaccel PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
set_property(TARGET vaccel PROPERTY LINK_FLAGS "-pthread")
set_property(TARGET vaccel PROPERTY C_STANDARD 11)
target_link_libraries(vaccel PRIVATE slog)

# Setup make install
install(TARGETS vaccel
	EXPORT vAccelTargets
	DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} PATTERN "*.in" EXCLUDE)

# Install vaccel-targets.cmake
install(EXPORT vAccelTargets
	FILE vaccel-targets.cmake
	DESTINATION "${CMAKE_INSTALL_DATADIR}"
	#	NAMESPACE YourLibrary::
)

# Install local vaccel-targets.cmake (build dir)
export(TARGETS vaccel FILE vaccel-targets.cmake)

# Create the pkg-config file
set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
CONFIGURE_FILE("vaccel.pc.in" "vaccel.pc" @ONLY)

# Install the vaccel.pc file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vaccel.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
