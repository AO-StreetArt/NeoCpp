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

#include <string>
#include <unordered_map>

#include "neocpp/data/interface/result_iterator_interface.h"
#include "neocpp/data/interface/query_parameter_interface.h"

#ifndef NEOCPP_CONNECTION_INTERFACE_NEO4J_INTERFACE_H_
#define NEOCPP_CONNECTION_INTERFACE_NEO4J_INTERFACE_H_

namespace Neocpp {

//! Neo4j Query Interface

//! Executes queries against the Neo4j DB.
//! Returns complex data structures for viewing
//! Query results, which start with the ResultsIteratorInterface
class Neo4jInterface {
 public:
  virtual ~Neo4jInterface() {}

  //! Execute the given Cypher Query
  virtual ResultsIteratorInterface* execute(const char * query) = 0;

  //! Execute the given Cypher Query
  virtual ResultsIteratorInterface* execute(std::string query) = 0;

  //! Execute a given Cypher Query with an input map of parameters
  virtual ResultsIteratorInterface* execute(const char * query, \
    std::unordered_map<std::string, Neo4jQueryParameterInterface*>\
    query_params) = 0;

  //! Execute a given Cypher Query with an input map of parameters
  virtual ResultsIteratorInterface* execute(std::string query, \
    std::unordered_map<std::string, Neo4jQueryParameterInterface*> \
    query_params) = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_CONNECTION_INTERFACE_NEO4J_INTERFACE_H_
