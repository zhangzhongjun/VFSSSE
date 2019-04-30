# please make sure that grpc++.pc and grpc.pc exist in PKG_CONFIG_PATH
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig


CXX = g++
CPPFLAGS += -I/usr/local/include -I/usr/local/include/cryptopp -I. -pthread
CXXFLAGS += -std=c++11 -O3
LDFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
           -lprotobuf -lrocksdb -lz -lcryptopp -lpthread -O3
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`


all: main

main : logger.o main.o
	$(CXX) $^ $(LDFLAGS) -o $@


clean:
	rm -f *.o main