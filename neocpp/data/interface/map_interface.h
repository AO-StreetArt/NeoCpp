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

#include "neocpp/data/interface/list_interface.h"
#include <string>

#ifndef NEOCPP_DATA_INTERFACE_NEO4J_MAP_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_NEO4J_MAP_INTERFACE_H_

namespace Neocpp {

//! A Neo4j Map

//! This is returned for map elements
//! in a map as well as node/edge properties
class DbMapInterface {
 public:
  virtual ~DbMapInterface() {}

  //! Get the size of the map
  virtual unsigned int size() = 0;

  //! Does an element exist in the map
  virtual bool element_exists(std::string key) = 0;

  //! Get a string element out of a map
  virtual std::string get_string_element(std::string key, \
    int char_buffer_size) = 0;

  //! Get a string element out of a map
  virtual std::string get_string_element(std::string key) = 0;

  //! Get a bool element out of a map
  virtual bool get_bool_element(std::string key) = 0;

  //! Get an int element out of a map
  virtual int get_int_element(std::string key) = 0;

  //! Get a float element out of a map
  virtual double get_float_element(std::string key) = 0;

  //! Get a list element out of a map
  virtual DbListInterface* get_list_element(std::string key) = 0;

  //! Get the string representation of the map
  virtual std::string to_string() = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_INTERFACE_NEO4J_MAP_INTERFACE_H_
