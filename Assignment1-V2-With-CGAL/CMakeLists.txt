CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (Assignment1-V2)

SET (CMAKE_CXX_STANDARD 11)

# CGAL config
# For linux CGAL to work also install package " libcgal-qt5-dev " as well
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("-- CGAL Library was found")
INCLUDE( ${CGAL_USE_FILE} )
INCLUDE( CGAL_CreateSingleSourceCGALProgram )
INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
INCLUDE_DIRECTORIES (BEFORE "../../include")

ADD_LIBRARY(geometry geometry.cpp)

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(tests tests.cpp)

TARGET_LINK_LIBRARIES (main geometry)
TARGET_LINK_LIBRARIES (tests geometry)
