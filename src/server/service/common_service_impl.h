#include <grpcpp/grpcpp.h>

#include "service.grpc.pb.h"

namespace sample::v1 {

class CommonServiceImpl final : public CommonService::Service {
    public:
        CommonServiceImpl() = default;
        ~CommonServiceImpl() = default;
        grpc::Status Ping(grpc::ServerContext* context, const PingRequest* request, PingResponse* response);
};


} // namespace sample::v1

