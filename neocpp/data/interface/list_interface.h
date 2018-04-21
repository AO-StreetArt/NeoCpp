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

#ifndef NEOCPP_DATA_INTERFACE_NEO4J_LIST_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_NEO4J_LIST_INTERFACE_H_

namespace Neocpp {

//! A Neo4j List

//! This is returned for list elements
//! in a map as well as node labels
class DbListInterface {
 public:
  virtual ~DbListInterface() {}

  //! Get a bool element out of a list
  virtual bool get_bool_element(unsigned int ind) = 0;

  //! Get an int element out of a list
  virtual int get_int_element(unsigned int ind) = 0;

  //! Get a float element out of a list
  virtual double get_float_element(unsigned int ind) = 0;

  //! Get a list string out of a list
  virtual std::string get_string_element(unsigned int ind, \
    int char_buffer_size) = 0;

  //! Get a string element out of a list
  virtual std::string get_string_element(unsigned int ind) = 0;

  //! Get the string representation of the list
  virtual std::string to_string() = 0;

  //! Get the size of a list
  virtual unsigned int size() = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_INTERFACE_NEO4J_LIST_INTERFACE_H_
