cmake_minimum_required(VERSION 3.10)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

project(person_rec)

find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

# Common proto files
set(person_proto_files
  ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf/animal.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf/house.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf/person.proto
)

# Person Receiver
set(person_rec_src
  src/person_rec.cpp
)

ecal_add_sample(${PROJECT_NAME} ${person_rec_src})
PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf ${person_proto_files})
target_link_libraries(${PROJECT_NAME}
  eCAL::core
  protobuf::libprotobuf
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

# Person Sender UDP
set(person_snd_udp_src
  src/person_snd_udp.cpp
)

ecal_add_sample(${PROJECT_NAME}_snd_udp ${person_snd_udp_src})
PROTOBUF_TARGET_CPP(${PROJECT_NAME}_snd_udp ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf ${person_proto_files})
target_link_libraries(${PROJECT_NAME}_snd_udp
  eCAL::core
  protobuf::libprotobuf
)
target_compile_features(${PROJECT_NAME}_snd_udp PRIVATE cxx_std_14)