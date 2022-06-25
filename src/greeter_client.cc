/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <time.h>
#include <stdio.h>
#include <stdint.h>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:50051";
  }
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("world");

  struct timespec t1,t2,t3,t4;
	int64_t d1,d2,d3,d4;
  std::string reply;

	clock_gettime(CLOCK_MONOTONIC, &t1);
  reply = greeter.SayHello(user);
	clock_gettime(CLOCK_MONOTONIC, &t2);
	
	for (int i=0;i< 10000;i++)
	{
		reply = greeter.SayHello(user);
	}
	clock_gettime(CLOCK_MONOTONIC, &t3);
	
  reply = greeter.SayHello(user);
	
	clock_gettime(CLOCK_MONOTONIC, &t4);
	
	d1 = t1.tv_sec * (1000 * 1000 * 1000) + t1.tv_nsec;
	d2 = t2.tv_sec * (1000 * 1000 * 1000) + t2.tv_nsec;
	d3 = t3.tv_sec * (1000 * 1000 * 1000) + t3.tv_nsec;
	d4 = t4.tv_sec * (1000 * 1000 * 1000) + t4.tv_nsec;
	
	
  std::cout << "Greeter received: " << reply << std::endl;

	
	printf("one shot time %ld(us)\n", (d2-d1)/1000);
	printf("avg time %ld(us)\n", (d3-d2)/1000/10000);
	printf("one shot time %ld(us)\n", (d4-d3)/1000);
	
  return 0;
}
