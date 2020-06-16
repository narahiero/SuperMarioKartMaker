########################################
# Add include directories
########################################

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_BINARY_DIR}/Source"
)


########################################
# Add subdirectories
########################################

add_subdirectory(Common)

add_subdirectory(UI)
