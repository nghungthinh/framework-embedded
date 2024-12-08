cmake_minimum_required(VERSION 3.3...3.15)
project(opendds)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(OpenDDS REQUIRED)

# IDL TypeSupport Library
add_library(messenger_idl)
opendds_target_sources(messenger_idl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Messenger.idl")
target_link_libraries(messenger_idl PUBLIC OpenDDS::Dcps)

list(APPEND PROJECT_SOURCES_COMMUNICATION
    MessengerC.cpp
    MessengerTypeSupportC.cpp
    MessengerTypeSupportImpl.cpp
)

# Main executable
add_executable(main 
    main.cpp
    src/service.cpp
    src/service_if.cpp
    src/client.cpp
    src/data_listener_reader_impl.cpp
)

target_include_directories(main 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ACE_ROOT}
    ${OPENDDS_ROOT}/ACE_wrappers
)

target_link_libraries(main
    PRIVATE
    messenger_idl
    OpenDDS::Dcps
    OpenDDS::Rtps
    OpenDDS::Rtps_Udp
    ${ACE_LIBRARIES}
)
