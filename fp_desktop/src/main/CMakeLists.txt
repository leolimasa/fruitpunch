cmake_minimum_required(VERSION 2.7)
project(fp_desktop)
set(CMAKE_SKIP_RPATH TRUE)

# ---------------------------------------------------------
# MAKE ECLIPSE HAPPY
# ---------------------------------------------------------
IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -g")
#SET(CMAKE_MOUDLE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -pg -g")
#SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg -g")


# ---------------------------------------------------------
# SOURCES
# ---------------------------------------------------------
file(GLOB_RECURSE sources "${fp_desktop_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE includes "${fp_desktop_SOURCE_DIR}/include/*.h")

include_directories(
	${fp_desktop_SOURCE_DIR}/include
)

# ---------------------------------------------------------
# BINARY
# ---------------------------------------------------------

# Uncomment if we ever need a library
#add_library(fp_desktop_static STATIC ${sources} ${includes})
#add_library(fp_desktop SHARED ${sources} ${includes})
#set_target_properties(fp_desktop_static PROPERTIES OUTPUT_NAME fp_desktop)

add_executable(fp_desktop ${sources})

# ---------------------------------------------------------
# LINKER
# ---------------------------------------------------------
target_link_libraries(fp_desktop
	fp_core
	pugixml
	Box2D
	armadillo
	util
	python2.7
	glfw3
	Xi
	Xrandr
	pthread
	Xxf86vm
	X11
	GL
	GLEW
	freetype
	boost_filesystem
    boost_system
    boost_python
    boost_program_options
    boost_date_time
	openal 
	ogg 
	vorbis 
	vorbisfile
	alut
)

install(TARGETS fp_desktop
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY ${fp_desktop_SOURCE_DIR}/include/ DESTINATION "include")

