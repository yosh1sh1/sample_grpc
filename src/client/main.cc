#include <iostream>
#include <string>

#include <grpcpp/grpcpp.h>

#include <spdlog/spdlog.h>

#include "service.grpc.pb.h"
#include "service.pb.h"

void call_common_service(const std::string endpoint) {

    std::shared_ptr<grpc::Channel> channel =
            grpc::CreateChannel(endpoint, grpc::InsecureChannelCredentials());
    std::unique_ptr<sample::v1::CommonService::Stub> stub =
            sample::v1::CommonService::NewStub(channel);

    grpc::ClientContext context;

    sample::v1::PingRequest request;
    request.set_name("test");

    sample::v1::PingResponse response;

    grpc::Status status = stub->Ping(&context, request, &response);
    if (!status.ok()) {
        std::cout << "Failed Ping." << std::endl;
        spdlog::error("error_code: {}, error_message: {}",
                static_cast<int32_t>(status.error_code()), status.error_message());
    }

    std::cout << response.message() << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid argument. argc: " << argc << std::endl;
        return 0;
    }

    call_common_service(argv[1]);

    return 0;
}