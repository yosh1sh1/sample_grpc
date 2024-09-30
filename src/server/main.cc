#include <iostream>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "service/common_service_impl.h"
#include "service.pb.h"

void run_server(std::string endpoint) {
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    grpc::ServerBuilder builder;

    builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());

    sample::v1::CommonServiceImpl service;
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << endpoint << std::endl;

    server->Wait();
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Invalid argument. argc: " << argc << std::endl;
        return 0;
    }

    run_server(argv[1]);

    return 0;
}