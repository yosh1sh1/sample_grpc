FROM amazonlinux:2023

RUN dnf install -y \
    gcc \
    gcc-c++ \
    gdb \
    cmake \
    make \
    python3.11-devel \
    python3.11-pip \
    less \
    wget \
    vi \
    git \
    which \
    procps \
    && dnf clean all

#
# gRPC
#
RUN git clone --recurse-submodules -b v1.66.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc \
    && cd grpc \
    && mkdir -p cmake/build \
    && pushd cmake/build \
    && cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          ../..\
    && make -j 4 \
    && make install \
    && popd \
    && cd .. \
    && rm -rf grpc

#
# spdlog(installed under /usr/local/include/spdlog)
#
RUN git clone https://github.com/gabime/spdlog.git \
    && cd spdlog && mkdir build && cd build \
    && cmake .. \
    && make -j \
    && make install \
    && cd ../../ \
    && rm -rf spdlog

CMD ["/bin/bash"]