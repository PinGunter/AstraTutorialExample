
set(SPV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/spv)

## localizar el paquete nvpro_core
if(NOT BASE_DIRECTORY)

find_path(BASE_DIRECTORY
NAMES nvpro_core/cmake/setup.cmake
PATHS ${CMAKE_CURRENT_SOURCE_DIR}/AstraEngine
REQUIRED
DOC "Directory containing nvpro_core"
)
endif()

## Various functions and macros REQUIRED
if(EXISTS ${BASE_DIRECTORY}/nvpro_core/cmake/setup.cmake)
include(${BASE_DIRECTORY}/nvpro_core/cmake/setup.cmake)
include(${BASE_DIRECTORY}/nvpro_core/cmake/utilities.cmake)
else()
message(FATAL_ERROR "could not find base directory, please set BASE_DIRECTORY to folder containing nvpro_core")
endif()

set(ASTRA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
add_definitions(/wd26812)  # 'enum class' over 'enum'
add_definitions(/wd26451)  # Arithmetic overflow, casting 4 byte value to 8 byte value
endif()

_add_package_VulkanSDK()
_add_package_ImGUI()
_add_nvpro_core_lib()

#--------------------------------------------------------------------------------------------------
add_subdirectory(AstraEngine/AstraCore)
include_directories(AstraEngine/AstraCore/include/ AstraEngine/AstraCore/shaders/)
