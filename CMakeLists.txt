cmake_minimum_required(VERSION 3.8)

project(sample_grpc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAEK_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# add_definitions(
#     -D_GLIBCXX_USE_CXX11_ABI=0
# )

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
    /lib64/
)

set(
    PROTOBUF_ABSL_DEPS
    absl_absl_check absl_absl_log absl_algorithm absl_base absl_bind_front absl_bits absl_btree absl_cleanup absl_cord absl_core_headers absl_debugging absl_die_if_null absl_dynamic_annotations absl_flags absl_flat_hash_map absl_flat_hash_set absl_function_ref absl_hash absl_layout absl_log_initialize absl_log_severity absl_memory absl_node_hash_map absl_node_hash_set absl_optional absl_span absl_status absl_statusor absl_strings absl_synchronization absl_time absl_type_traits absl_utility absl_variant
)

set(ABSL_LIBS
    libabsl_bad_any_cast_impl.a
    libabsl_bad_optional_access.a
    libabsl_bad_variant_access.a
    libabsl_base.a
    libabsl_city.a
    libabsl_civil_time.a
    libabsl_cord.a
    libabsl_cord_internal.a
    libabsl_cordz_functions.a
    libabsl_cordz_handle.a
    libabsl_cordz_info.a
    libabsl_cordz_sample_token.a
    libabsl_crc32c.a
    libabsl_crc_cord_state.a
    libabsl_crc_cpu_detect.a
    libabsl_crc_internal.a
    libabsl_debugging_internal.a
    libabsl_demangle_internal.a
    libabsl_die_if_null.a
    libabsl_examine_stack.a
    libabsl_exponential_biased.a
    libabsl_failure_signal_handler.a
    libabsl_flags_commandlineflag.a
    libabsl_flags_commandlineflag_internal.a
    libabsl_flags_config.a
    libabsl_flags_internal.a
    libabsl_flags_marshalling.a
    libabsl_flags_parse.a
    libabsl_flags_private_handle_accessor.a
    libabsl_flags_program_name.a
    libabsl_flags_reflection.a
    libabsl_flags_usage.a
    libabsl_flags_usage_internal.a
    libabsl_graphcycles_internal.a
    libabsl_hash.a
    libabsl_hashtablez_sampler.a
    libabsl_int128.a
    libabsl_kernel_timeout_internal.a
    libabsl_leak_check.a
    libabsl_log_entry.a
    libabsl_log_flags.a
    libabsl_log_globals.a
    libabsl_log_initialize.a
    libabsl_log_internal_check_op.a
    libabsl_log_internal_conditions.a
    libabsl_log_internal_fnmatch.a
    libabsl_log_internal_format.a
    libabsl_log_internal_globals.a
    libabsl_log_internal_log_sink_set.a
    libabsl_log_internal_message.a
    libabsl_log_internal_nullguard.a
    libabsl_log_internal_proto.a
    libabsl_log_severity.a
    libabsl_log_sink.a
    libabsl_low_level_hash.a
    libabsl_malloc_internal.a
    libabsl_periodic_sampler.a
    libabsl_random_distributions.a
    libabsl_random_internal_distribution_test_util.a
    libabsl_random_internal_platform.a
    libabsl_random_internal_pool_urbg.a
    libabsl_random_internal_randen.a
    libabsl_random_internal_randen_hwaes.a
    libabsl_random_internal_randen_hwaes_impl.a
    libabsl_random_internal_randen_slow.a
    libabsl_random_internal_seed_material.a
    libabsl_random_seed_gen_exception.a
    libabsl_random_seed_sequences.a
    libabsl_raw_hash_set.a
    libabsl_raw_logging_internal.a
    libabsl_scoped_set_env.a
    libabsl_spinlock_wait.a
    libabsl_stacktrace.a
    libabsl_status.a
    libabsl_statusor.a
    libabsl_str_format_internal.a
    libabsl_strerror.a
    libabsl_string_view.a
    libabsl_strings.a
    libabsl_strings_internal.a
    libabsl_symbolize.a
    libabsl_synchronization.a
    libabsl_throw_delegate.a
    libabsl_time.a
    libabsl_time_zone.a
    libabsl_vlog_config_internal.a

    # absl::absl_check
    # absl::absl_log
    # absl::algorithm
    # absl::base
    # absl::bind_front
    # absl::bits
    # absl::btree
    # absl::cleanup
    # absl::cord
    # absl::core_headers
    # absl::debugging
    # absl::die_if_null
    # absl::dynamic_annotations
    # absl::flags
    # absl::flat_hash_map
    # absl::flat_hash_set
    # absl::function_ref
    # absl::hash
    # absl::layout
    # absl::log_initialize
    # absl::log_severity
    # absl::memory
    # absl::node_hash_map
    # absl::node_hash_set
    # absl::optional
    # absl::span
    # absl::status
    # absl::statusor
    # absl::strings
    # absl::synchronization
    # absl::time
    # absl::type_traits
    # absl::utility
    # absl::variant
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

target_link_libraries(
    proto_domain
    PUBLIC
    protobuf
    # ${ABSL_LIBS}
    # absl::check
    # absl::flags
    # absl::flags_parse
    # absl::log
    # ${PROTOBUF_ABSL_DEPS}
    # absl_flags
    # absl_flags_parse
    gRPC::grpc++
    gRPC::grpc++_reflection
)

#
# server
#
file(
    GLOB_RECURSE
    GRPC_SAMPLE_SERVER_FILES
    ${PROJECT_SOURCE_DIR}/src/server/*.cc
)

add_executable(${PROJECT_NAME}_server ${GRPC_SAMPLE_SERVER_FILES})

target_include_directories(
    ${PROJECT_NAME}_server
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/server
    # ${PROJECT_SOURCE_DIR}/src/client
    ${PROJECT_SOURCE_DIR}/generated-sources
    # /include # for grpc
    # /usr/local/include
)

target_link_libraries(
    ${PROJECT_NAME}_server
    PUBLIC
    proto_domain
    protobuf
    # ${PROTOBUF_ABSL_DEPS}
    # ${ABSL_LIBS}
    # absl::check
    # absl::flags
    # absl::flags_parse
    # absl::log
    # absl_flags
    # absl_flags_parse
    # utf8_validity
    gRPC::grpc++
    gRPC::grpc++_reflection
    # gRPC::grpc++_unsecure
)

#
# client
#
file(
    GLOB_RECURSE
    GRPC_SAMPLE_SERVER_FILES
    ${PROJECT_SOURCE_DIR}/src/client/*.cc
)

add_executable(${PROJECT_NAME}_client ${GRPC_SAMPLE_SERVER_FILES})

target_include_directories(
    ${PROJECT_NAME}_client
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/client
    ${PROJECT_SOURCE_DIR}/generated-sources
    # /include # for grpc
    # /usr/local/include
)

target_link_libraries(
    ${PROJECT_NAME}_client
    PUBLIC
    proto_domain
    protobuf
    # ${PROTOBUF_ABSL_DEPS}
    # ${ABSL_LIBS}
    # absl::check
    # absl::flags
    # absl::flags_parse
    # absl::log
    # absl_flags
    # absl_flags_parse
    # utf8_validity
    gRPC::grpc++
    gRPC::grpc++_reflection
    # gRPC::grpc++_unsecure
)
