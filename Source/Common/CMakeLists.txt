########################################
# Configure Version.hpp
########################################

configure_file(Version.hpp.in Version.hpp @ONLY)


########################################
# Setup target
########################################

add_library(Common STATIC
    DataChunk.cpp
    DataChunk.hpp
    Observable.cpp
    Observable.hpp
    Property.hpp
)

# Set C++ settings
target_compile_features(Common PUBLIC cxx_std_17)
set_target_properties(Common PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(Common ${CommonDeps})
