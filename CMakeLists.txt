cmake_minimum_required (VERSION 3.1)
project (AircraftCalc)
set (CMAKE_CXX_STANDARD 11)

#VERSION
set (AircraftCalc_VERSION_MAJOR 1)
set (AircraftCalc_VERSION_MINOR 0)
set (AircraftCalc_VERSION_PATCH 0)
set (AircraftCalc_VERSION
  ${AircraftCalc_VERSION_MAJOR}.${AircraftCalc_VERSION_MINOR}.${AircraftCalc_VERSION_PATCH})

#SOURCE CODE
set(SOURCES 
  main.cpp
  core/Carrier.cpp
  core/Plane.cpp
  core/io.cpp
  core/belongingStructure.cpp
  core/global.cpp
  core/core.cpp
  core/formular.cpp
  core/atkdp.cpp
  core/calculator.cpp
)

#EXECUTABLE
add_executable (AircraftCalc ${SOURCES})
