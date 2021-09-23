add_subdirectory(src)
include_directories(${MyProject_SOURCE_DIR}/Libraries)
add_library(EDITEUR editeur.c)