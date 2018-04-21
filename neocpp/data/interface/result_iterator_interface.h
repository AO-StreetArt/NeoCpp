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

#ifndef NEOCPP_DATA_INTERFACE_RESULT_ITERATOR_INTERFACE_H_
#define NEOCPP_DATA_INTERFACE_RESULT_ITERATOR_INTERFACE_H_

namespace Neocpp {

//! Results Iterator for viewing query results

//! Accepts a result stream as an input, returns Results
//! Trees for each entry that matches in the query
//! Deletes it when finished
class ResultsIteratorInterface {
 public:
  virtual ~ResultsIteratorInterface() {}

  //! Clear the results iterator of all values
  virtual void clear() = 0;

  //! Is the iterator empty?

  //! Return true if this iterator contains no results.
  //! Return false otherwise.
  virtual bool empty() = 0;

  //! Get the number of results in the query
  virtual unsigned int length() = 0;

  //! Get the next query result
  virtual ResultTreeInterface* next() = 0;
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_INTERFACE_RESULT_ITERATOR_INTERFACE_H_
