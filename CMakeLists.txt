cmake_minimum_required(VERSION 3.9.6 FATAL_ERROR)
project(MiAplicacion)

include(AstraEngine/setup.cmake)

set(PROJNAME ${PROJECT_NAME})
project(${PROJNAME} LANGUAGES C CXX)
message(STATUS "-------------------------------")
message(STATUS "Processing Project ${PROJNAME}:")


#--------------------------------------------------------------------------------------------------
# C++ target and defines
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJNAME})
file(GLOB SOURCE_FILES src/*.cpp include/*.h)
include_directories(include)
_add_project_definitions(${PROJNAME})

#--------------------------------------------------------------------------------------------------
# GLSL to SPIR-V custom build
compile_glsl_directory(
	SRC "${CMAKE_CURRENT_SOURCE_DIR}/shaders" 
	DST "${SPV_DIR}/${PROJNAME}/" 
	VULKAN_TARGET "vulkan1.2"
	DEPENDENCY ${VULKAN_BUILD_DEPENDENCIES}
	
)
target_link_libraries(${PROJNAME} AstraCore) 

#--------------------------------------------------------------------------------------------------
# Sources
target_sources(${PROJNAME} PUBLIC ${SOURCE_FILES} ${HEADER_FILES})
target_sources(${PROJNAME} PUBLIC ${COMMON_SOURCE_FILES})
target_sources(${PROJNAME} PUBLIC ${PACKAGE_SOURCE_FILES})
target_sources(${PROJNAME} PUBLIC ${GLSL_SOURCES} ${GLSL_HEADERS})
	
	
#--------------------------------------------------------------------------------------------------
# Linkage
#
target_link_libraries(${PROJNAME} ${PLATFORM_LIBRARIES} nvpro_core)
	
foreach(DEBUGLIB ${LIBRARIES_DEBUG})
	target_link_libraries(${PROJNAME} debug ${DEBUGLIB})
endforeach(DEBUGLIB)
	
foreach(RELEASELIB ${LIBRARIES_OPTIMIZED})
	target_link_libraries(${PROJNAME} optimized ${RELEASELIB})
endforeach(RELEASELIB)
	
#--------------------------------------------------------------------------------------------------
# copies binaries that need to be put next to the exe files (ZLib, etc.)
#
_finalize_target( ${PROJNAME} )