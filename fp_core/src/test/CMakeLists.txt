cmake_minimum_required(VERSION 2.7)
project(fp_core_test)

# ---------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------
find_library(Box2D NAMES libBox2D.a)

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
# SOURCE AND HEADERS
# ---------------------------------------------------------
file(GLOB_RECURSE sources "${fp_core_test_SOURCE_DIR}/src/*.cpp")
include_directories(
	${fp_core_test_SOURCE_DIR}/include
	${fp_core_test_SOURCE_DIR}/../main/include
	${fp_core_test_SOURCE_DIR}/../../target/dependencies/include
)

# ---------------------------------------------------------
# BINARY
# ---------------------------------------------------------
add_executable(fp_core_test ${sources})

# ---------------------------------------------------------
# LINKER
# ---------------------------------------------------------
target_link_libraries(fp_core_test 
	fp_core
	Box2D
	png
	gtest
	armadillo
	util
	python2.7
	boost_system
	boost_filesystem
        boost_date_time
        boost_python
	GL
	GLEW
	cairo
	freetype
	ogg 
	vorbis 
	vorbisfile
)
