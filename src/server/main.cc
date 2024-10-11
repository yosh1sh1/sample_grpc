#include <iostream>
#include <string>

#include <spdlog/spdlog.h>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "service/common_service_impl.h"
#include "service.pb.h"

void run_server(const std::string endpoint) {
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    grpc::ServerBuilder builder;

    builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
    
    // デフォルト 送信最大サイズ：無制限
    // デフォルト 受信最大サイズ：4MB
    // builder.SetMaxSendMessageSize(std::numeric_limits<int>::max());
    // builder.SetMaxRecvMessageSize(std::numeric_limits<int>::max());

    sample::v1::CommonServiceImpl service;
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    spdlog::info("Server listening on {}", endpoint);

    server->Wait();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        spdlog::error("Invalid argument. argc:  {}", argc);
        return 0;
    }

    run_server(argv[1]);

    return 0;
}