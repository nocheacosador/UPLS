file(GLOB ${sample_library}_sources *.cpp)

add_library(${sample_library} STATIC ${${sample_library}_sources})
set_property(TARGET ${sample_library} PROPERTY PREFIX "")
target_compile_definitions(${sample_library} PRIVATE BINDINGS_BUILD)
