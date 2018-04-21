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
#include "neocpp/data/interface/map_interface.h"
#include "neocpp/data/interface/list_interface.h"

#ifndef NEOCPP_DATA_INTERFACE_NEO4J_OBJECT_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_NEO4J_OBJECT_INTERFACE_H_

namespace Neocpp {

//! A Neo4j Object

//! This is returned from a result tree and
//! represents either a node, an edge, or a path
class DbObjectInterface {
 public:
  virtual ~DbObjectInterface() {}

  //! Is this a node?

  //! Return true if this is a node object.
  //! Return false if this is an edge or path object.
  virtual bool is_node() = 0;

  //! Is this an edge?

  //! Return false if this is a node or path object.
  //! Return true if this is an edge object.
  virtual bool is_edge() = 0;

  //! Is this a path?

  //! Return false if this is a node or edge object.
  //! Return true if this is a path object.
  virtual bool is_path() = 0;

  //! Get the string representation of the object
  virtual std::string to_string() = 0;

  //! Get the properties of the object

  //! This functions for both node objects and
  //! edge objects
  virtual DbMapInterface* properties() = 0;

  //! Get the labels of the node

  //! This functions only for node
  //! objects
  virtual DbListInterface* labels() = 0;

  //! Get the type of the edge

  //! This functions only for edge
  //! objects
  virtual std::string type() = 0;

  //! Was the edge traversed in it's natural direction?

  //! This functions only for edge objects which
  //! were taken from a Path
  virtual bool forward() = 0;

  //! Get the size of the path

  //! This functions only for path
  //! objects
  virtual unsigned int size() = 0;

  //! Get an element from a path object

  //! Get an element from a path at the specified index.
  //! This functions only for path objects
  virtual DbObjectInterface* get_path_element(int path_index) = 0;
};

}

#endif  // NEOCPP_DATA_INTERFACE_NEO4J_OBJECT_INTERFACE_H_
