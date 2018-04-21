/*
Apache 2.0 License

Copyright 2018 Alex Barry

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef NEO4CPP_UTILS_NEO4J_EXCEPTION_H_
#define NEO4CPP_UTILS_NEO4J_EXCEPTION_H_

#include <string>
#include <exception>

namespace Neocpp {

//! Neo4j Exception

//! A child class of std::exception which holds error information for a
//! Neo4j connection.  Can be thrown by the Neo4cpp interfaces.
struct Neo4jException: public std::exception {
  // An error message passed on initialization
  std::string int_msg;
  const char * int_msg_cstr;
  neo4j_result_stream_t *results = NULL;

  // Create a Neo4j Exception, and store the given error message
  inline Neo4jException(std::string msg) {
    int_msg = "Error in Neo4j Request: " + msg;
    int_msg_cstr = int_msg.c_str();
  }

  inline Neo4jException(std::string msg, neo4j_result_stream_t *r) {
    int_msg = "Error in Neo4j Request: " + msg;
    int_msg_cstr = int_msg.c_str();
    results = r;
  }

  Neo4jException() {}
  ~Neo4jException() throw() {if (results) {neo4j_close_results(results);}}
  //! Show the error message in readable format
  const char * what() const throw() {
    return int_msg_cstr;
  }
};

} // namespace neocpp

#endif  // NEO4CPP_UTILS_NEO4J_EXCEPTION_H_
