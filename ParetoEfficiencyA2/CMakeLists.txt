CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (ParetoEfficiencyA2)

SET (ParetoEfficiencyA2_VERSION_MAJOR 1)
SET (ParetoEfficiencyA2_VERSION_MINOR 0)
SET (CMAKE_CXX_STANDARD 11)

# first one is a label (arbitrary), second is the file name of the library
ADD_LIBRARY(geometry Pareto.cpp)

# first name is the name of the executeable, second is the entrance point for the exe
ADD_EXECUTABLE(ParetoEfficiency main.cpp)
#ADD_EXECUTABLE(tests tests.cpp)

# first one is the target (executable), second is the library you add
TARGET_LINK_LIBRARIES (ParetoEfficiency geometry)
#TARGET_LINK_LIBRARIES (tests geometry)
