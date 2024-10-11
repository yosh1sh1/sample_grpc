### 概要

gRPCのサンプルプログラム

### ファイル構成

```
sample_grpc
    ├── CMakeLists.txt
    ├── Dockerfile
    ├── Makefile
    ├── README.md
    ├── cmake
    ├── docker-compose.yml
    ├── generated-sources       // .protoのビルド先を配置
    ├── proto                   // .protoファイルを配置
    └── src
        ├── client              // クライアント側コードを配置
        └── server              // サーバー側コードを配置
```


### ビルド手順

```
$ make up
$ make shell
$ make build
$ make install
```

### 実行方法

#### サーバー起動

```
$ ./bin/sample_grpc_server localhost:50051
```


#### クライアント実行

```
$ ./bin/sample_grpc_client localhost:50051
```

