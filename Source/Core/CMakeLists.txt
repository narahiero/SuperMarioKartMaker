########################################
# Setup target
########################################

add_library(Core STATIC
)

# Set C++ settings
target_compile_features(Core PUBLIC cxx_std_17)
set_target_properties(Core PROPERTIES CXX_EXTENSIONS OFF)
