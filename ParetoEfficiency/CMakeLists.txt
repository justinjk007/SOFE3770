CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (ParetoEfficiency)

SET (ParetoEfficiency_VERSION_MAJOR 1)
SET (ParetoEfficiency_VERSION_MINOR 0)
SET (CMAKE_CXX_STANDARD 11)

# CGAL config
# For linux CGAL to work also install package " libcgal-qt5-dev " as well
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("-- CGAL Library was found")
INCLUDE( ${CGAL_USE_FILE} )
INCLUDE( CGAL_CreateSingleSourceCGALProgram )
INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
INCLUDE_DIRECTORIES (BEFORE "../../include")

# first one is a label (arbitrary), second is the file name of the library
ADD_LIBRARY(Pareto Pareto.cpp)
ADD_LIBRARY(ConvexHull ConvexHull.cpp)

# first name is the name of the executeable, second is the entrance point for the exe
ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests tests.cpp)

# first one is the target (executable), second is the library you add
TARGET_LINK_LIBRARIES (main Pareto ConvexHull)
TARGET_LINK_LIBRARIES (run_tests Pareto ConvexHull)
