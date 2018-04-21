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

#include <neo4j-client.h>

#ifndef NEOCPP_DATA_INTERFACE_QUERY_PARAMETER_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_QUERY_PARAMETER_INTERFACE_H_

namespace Neocpp {

//! Neo4j Query Parameter Interface

//! A query parameter to be inserted into a
//! Query prior to execution.  This could be
//! Either a single value or a list
class Neo4jQueryParameterInterface {
 public:
  virtual ~Neo4jQueryParameterInterface() {}

  //! Get the type of the query parameter
  virtual int get_type() = 0;

  //! Get the boolean value, if any
  virtual bool get_boolean_value() = 0;

  //! Get the boolean value at the specified index, if any
  virtual bool get_boolean_value(int index) = 0;

  //! Get the string value, if any
  virtual std::string get_string_value() = 0;

  //! Get the string value at the specified index, if any
  virtual std::string get_string_value(int index) = 0;

  //! Get the string value as a c string
  virtual const char * get_cstring_value() = 0;

  //! Get the integer value, if any
  virtual int get_integer_value() = 0;

  //! Get the integer value at the specified index, if any
  virtual int get_integer_value(int index) = 0;

  //! Get the double value, if any
  virtual double get_double_value() = 0;

  //! Get the double value at the specified index, if any
  virtual double get_double_value(int index) = 0;

  //! If the parameter is an array, return true
  virtual bool is_array() = 0;

  //! If the parameter is an array, return the size
  virtual unsigned int size() = 0;

  //! Add a float value to the array parameter
  virtual void add_value(float new_val) = 0;

  //! Add an integer value to the array parameter
  virtual void add_value(int new_val) = 0;

  //! Add a boolean value to the array parameter
  virtual void add_value(bool new_val) = 0;

  //! Add a string value to the array parameter
  virtual void add_value(std::string new_val) = 0;

  //! Add a string value to the array parameter
  virtual void add_value(const char * new_val) = 0;

  // Internal Use only - Used by Neo4j Admin when executing query.
  virtual neo4j_value_t get_neo4j_list() = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_INTERFACE_QUERY_PARAMETER_INTERFACE_H_
