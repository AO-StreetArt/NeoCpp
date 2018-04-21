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

#include "neocpp/data/interface/result_tree_interface.h"
#include "neocpp/data/interface/object_interface.h"
#include "neocpp/data/impl/neo4j_object.h"
#include <neo4j-client.h>
#include <string>

#ifndef NEOCPP_DATA_IMPL_NEO4J_RESULT_TREE_H_
#define NEOCPP_DATA_IMPL_NEO4J_RESULT_TREE_H_

namespace Neocpp {

// Represents a single query Result, returned by the iterator
// Consists of a set of nodes and edges
class ResultTree: public ResultTreeInterface {
  neo4j_result_t *result = NULL;
 public:
  ResultTree(neo4j_result_t *r) {result = r;}
  ~ResultTree() {}
  bool exists() {if (result) {return true;} else {return false;}}
  DbObjectInterface* get(int index) {return new DbObject(result, index);}
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_IMPL_NEO4J_RESULT_TREE_H_
