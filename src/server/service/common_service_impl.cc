#include <spdlog/spdlog.h>

#include "common_service_impl.h"

namespace sample::v1 {

grpc::Status CommonServiceImpl::Ping(grpc::ServerContext*, const PingRequest* request, PingResponse* response) {
    spdlog::info("Start Ping in CommonService");

    if (request->name().empty()) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "need to set 'name'.");
    }

    spdlog::info("PingRequest, name : {}", request->name());

    response->set_message("Hello! " + request->name() + ".");

    spdlog::info("Finish Ping in CommonService");

    return grpc::Status::OK;
}


} // namespace sample::v1

