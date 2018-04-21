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

#include "neocpp/utils/neo4j_exception.h"
#include "neocpp/data/impl/neo4j_result_tree.h"
#include "neocpp/data/interface/result_tree_interface.h"
#include "neocpp/data/interface/result_iterator_interface.h"
#include "neocpp/connection/impl/neo4j_connection_pool.h"

#ifndef NEOCPP_DATA_IMPL_NEO4J_RESULT_ITERATOR_H_
#define NEOCPP_DATA_IMPL_NEO4J_RESULT_ITERATOR_H_

namespace Neocpp {

// Results Iterator, accepts a result stream as an input,
// Returns Results Trees for each entry that matches in the query
// Deletes it when finished
// Also responsible for releasing the database connection after usage
class ResultsIterator: public ResultsIteratorInterface {
  neo4j_result_stream_t *results;
  Neo4jQuerySession *s;
  Neo4jConnectionPool *p;
  inline void clear_results() {
    if (neo4j_close_results(results) != 0) {
      const char * err_string = strerror(errno);
      std::string err_msg(err_string);
      err_msg = "Error clearing results from memory: " + err_msg;
      throw Neo4jException(err_msg);
    }
  }

 public:
  inline ResultsIterator(neo4j_result_stream_t *result_stream, \
    Neo4jQuerySession *session, Neo4jConnectionPool *pool) {
    results = result_stream;
    if ( !(results) || neo4j_nfields(results) < 0 ) {
      std::string err_msg(strerror(errno));
      err_msg = "Failed to fetch results" + err_msg;
      p->release_connection(s);
      throw Neo4jException(err_msg);
    }
    s = session;
    p = pool;
  }
  ~ResultsIterator() {clear_results(); p->release_connection(s);}
  void clear() {clear_results();}
  bool empty() {if (!results) {return true;} return false;}
  unsigned int length() {return neo4j_nfields(results);}
  inline ResultTreeInterface* next() {
    neo4j_result_t *res = neo4j_fetch_next(results);
    if (!res) {return NULL;} else {return new ResultTree(res);}
  }
};

} // namespace Neocpp

#endif  // NEOCPP_DATA_IMPL_NEO4J_RESULT_ITERATOR_H_
