AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# protbuf
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) --cpp_out=. $<

dist_noinst_DATA = helloworld.proto

# Gen. by protoc 
GRPC_GEN_FILES = \
	helloworld.pb.cc \
	helloworld.pb.h \
	helloworld.grpc.pb.cc \
	helloworld.grpc.pb.h 

MOSTLYCLEANFILES = ${GRPC_GEN_FILES}

# C/C++ sources
bin_PROGRAMS = \
	greeter_server greeter_client \
	greeter_server_local greeter_client_local

greeter_server_SOURCES = \
	${GRPC_GEN_FILES} \
	greeter_server.cc 

greeter_server_LDADD = \
	-lrt -lpthread \
	-lgrpc++_reflection \
	@PROTOBUF_LIBS@ \
	@GRPCPP_LIBS@ 

# C compiler options
greeter_server_CFLAGS = \
	-I$(top_srcdir)/include \
	@PROTOBUF_CFLAGS@ \
	@GRPCPP_CFLAGS@ \
	-D_GNU_SOURCE

# CXX compiler options
greeter_server_CXXFLAGS = \
	-I$(top_srcdir)/include \
	@PROTOBUF_CFLAGS@ \
	@GRPCPP_CFLAGS@ \
	-D_GNU_SOURCE

# Linker options
greeter_server_LDFLAGS = 


# C/C++ sources
greeter_client_SOURCES = \
	${GRPC_GEN_FILES} \
	greeter_client.cc 

greeter_client_LDADD = \
	-lrt -lpthread \
	@PROTOBUF_LIBS@ \
	@GRPCPP_LIBS@ 

# C compiler options
greeter_client_CFLAGS = \
	-I$(top_srcdir)/include \
	@PROTOBUF_CFLAGS@ \
	@GRPCPP_CFLAGS@ \
	-D_GNU_SOURCE

# CXX compiler options
greeter_client_CXXFLAGS = \
	-I$(top_srcdir)/include \
	@PROTOBUF_CFLAGS@ \
	@GRPCPP_CFLAGS@ \
	-D_GNU_SOURCE


##
greeter_server_local_SOURCES = \
	${GRPC_GEN_FILES} \
	greeter_server_local.cc 

greeter_server_local_LDADD = ${greeter_server_LDADD}
greeter_server_local_CFLAGS = ${greeter_server_CFLAGS}
greeter_server_local_CXXFLAGS = ${greeter_server_CXXFLAGS}

greeter_client_local_SOURCES = \
	${GRPC_GEN_FILES} \
	greeter_client_local.cc 

greeter_client_local_LDADD = ${greeter_client_LDADD}
greeter_client_local_CFLAGS = ${greeter_client_CFLAGS}
greeter_client_local_CXXFLAGS = ${greeter_client_CXXFLAGS}

