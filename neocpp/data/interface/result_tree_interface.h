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

#include "neocpp/data/interface/object_interface.h"

#ifndef NEOCPP_DATA_INTERFACE_RESULT_TREE_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_RESULT_TREE_INTERFACE_H_

namespace Neocpp {

//! Tree of Query Results

// Represents a single query Result, returned by the iterator
// Consists of a set of nodes and edges
class ResultTreeInterface {
 public:
  virtual ~ResultTreeInterface() {}

  //! Get the node/edge at the specified index
  virtual DbObjectInterface* get(int index) = 0;

  virtual bool exists() = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_INTERFACE_RESULT_TREE_INTERFACE_H_
