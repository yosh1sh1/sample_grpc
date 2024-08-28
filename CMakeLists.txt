cmake_minimum_required(VERSION 3.8)

project(sample_grpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAEK_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_definitions(
    -D_GLIBCXX_USE_CXX11_ABI=0
)

add_link_options(
    -Wl,-Bsymbolic
    -Wl,--exclude-libs,ALL
)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(
        # 最適化など
    ) 
endif()

set(CMAKE_EXE_LIKNER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")

link_directories(
    # /usr/local/lib
)

#
# .proto -> .cc/.h
#
file(
    GLOB_RECURSE
    PROTOFILES
    ${PROJECT_SOURCE_DIR}/proto/*.proto
)

add_library(proto_domain ${PROTOFILES})

get_target_property(
    grpc_cpp_plugin_location
    gRPC::grpc_cpp_plugin
    LOCATION
)

target_include_directories(
    proto_domain
    PUBLIC
    /include # google/protobuf
)
# target_link_libraries(proto_domain PUBLIC protobuf::libprotobuf gRPC::grpc++)

protobuf_generate(
    TARGET proto_domain
    LANGUAGE cpp
    IMPORT_DIRS ${PROJECT_SOURCE_DIR}/proto
    PROTOC_OUT_DIR ${PROTO_OUT}
)

protobuf_generate(
    TARGET proto_domain
    LANGUAGE grpc
    IMPORT_DIRS ${PROJECT_SOURCE_DIR}/proto
    PROTOC_OUT_DIR ${PROTO_OUT}

    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)

target_include_directories(
    proto_domain
    PUBLIC
    ${PROTO_OUT}
)

#
# main
#