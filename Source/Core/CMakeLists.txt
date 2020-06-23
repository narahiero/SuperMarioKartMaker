########################################
# Setup target
########################################

add_library(Core STATIC
    Callbacks.cpp
    Callbacks.hpp
    Core.cpp
    Core.hpp
    Project.cpp
    Project.hpp
)

# Set C++ settings
target_compile_features(Core PUBLIC cxx_std_17)
set_target_properties(Core PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(Core Common)
