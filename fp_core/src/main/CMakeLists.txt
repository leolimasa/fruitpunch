cmake_minimum_required(VERSION 2.7)
project(fp_core)
set(CMAKE_SKIP_RPATH TRUE)

# ---------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------
find_library(Box2D NAMES Box2D)

# ---------------------------------------------------------
# MAKE ECLIPSE HAPPY
# ---------------------------------------------------------
IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


# ---------------------------------------------------------
# SOURCES
# ---------------------------------------------------------
file(GLOB_RECURSE sources "${fp_core_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE includes "${fp_core_SOURCE_DIR}/include/*.h")

include_directories(
	${fp_core_SOURCE_DIR}/include
	${fp_core_SOURCE_DIR}/../../target/dependencies/include
)

# ---------------------------------------------------------
# BINARY
# ---------------------------------------------------------
add_library(fp_core_static STATIC ${sources} ${includes})
add_library(fp_core SHARED ${sources} ${includes})

set_target_properties(fp_core_static PROPERTIES OUTPUT_NAME fp_core)

# ---------------------------------------------------------
# LINKER
# ---------------------------------------------------------
target_link_libraries(fp_core
	${Box2D}
	pugixml
	armadillo
	util
	python2.7
	GL
	GLEW
	cairo
	freetype
	boost_date_time
        boost_system
	boost_filesystem
	boost_python
	ogg
	vorbis 
	vorbisfile
)

install(TARGETS fp_core_static fp_core
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY ${fp_core_SOURCE_DIR}/include/ DESTINATION "include")
