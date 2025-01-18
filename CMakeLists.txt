cmake_minimum_required(VERSION 3.22)

if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
	message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
	message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
	message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()

include(${METAMODULE_SDK_DIR}/plugin.cmake)


project(SVModularMetaModulePlugin
    VERSION     0.1
    DESCRIPTION "SVModular Plugin for MetaModule"
    LANGUAGES   C CXX ASM
)

add_library(DrumKit STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(DrumKit
    PRIVATE
    ${SOURCE_DIR}/deps/ADSR.cpp
    ${SOURCE_DIR}/deps/LFO.cpp
    ${SOURCE_DIR}/deps/LFO.cpp
    ${SOURCE_DIR}/deps/SynthDevKit/src/CV.cpp

    ${SOURCE_DIR}/src/controller/Baronial.cpp
    ${SOURCE_DIR}/src/controller/BD9.cpp
    ${SOURCE_DIR}/src/controller/CR78.cpp
    ${SOURCE_DIR}/src/controller/ClosedHH.cpp
    ${SOURCE_DIR}/src/controller/DMX.cpp
    ${SOURCE_DIR}/src/controller/Gnome.cpp
    ${SOURCE_DIR}/src/controller/OpenHH.cpp
    ${SOURCE_DIR}/src/controller/Marionette.cpp
    ${SOURCE_DIR}/src/controller/SBD.cpp
    ${SOURCE_DIR}/src/controller/SampleController.cpp
    ${SOURCE_DIR}/src/controller/Sequencer.cpp
    ${SOURCE_DIR}/src/controller/Snare.cpp
    ${SOURCE_DIR}/src/controller/Tomi.cpp

    ${SOURCE_DIR}/src/model/SampleManager.cpp

    ${SOURCE_DIR}/src/view/Baronial.cpp
    ${SOURCE_DIR}/src/view/BD9.cpp
    ${SOURCE_DIR}/src/view/CR78.cpp
    ${SOURCE_DIR}/src/view/ClosedHH.cpp
    ${SOURCE_DIR}/src/view/DMX.cpp
    ${SOURCE_DIR}/src/view/Gnome.cpp
    ${SOURCE_DIR}/src/view/Marionette.cpp
    ${SOURCE_DIR}/src/view/OpenHH.cpp
    ${SOURCE_DIR}/src/view/SBD.cpp
    ${SOURCE_DIR}/src/view/Sequencer.cpp
    ${SOURCE_DIR}/src/view/Snare.cpp
    ${SOURCE_DIR}/src/view/Tomi.cpp

    ${SOURCE_DIR}/src/DrumKit.cpp
)

target_include_directories(DrumKit PRIVATE
    ${SOURCE_DIR}
)

set_property(TARGET DrumKit PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      DrumKit                     # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     DrumKit                     # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json   # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${SOURCE_DIR}/assets        # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}              # Path to where you want the plugin file output
)
