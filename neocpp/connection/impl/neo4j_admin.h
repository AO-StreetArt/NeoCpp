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

#include <stdio.h>
#include <errno.h>
#include <neo4j-client.h>
#include <string>
#include <exception>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <mutex>

#include "neocpp/connection/interface/neo4j_interface.h"
#include "neocpp/connection/impl/neo4j_connection_pool.h"
#include "neocpp/data/interface/result_iterator_interface.h"
#include "neocpp/data/impl/neo4j_result_iterator.h"
#include "neocpp/utils/neo4j_exception.h"

#ifndef NEOCPP_CONNECTION_IMPL_NEO4J_ADMIN_H_
#define NEOCPP_CONNECTION_IMPL_NEO4J_ADMIN_H_

namespace Neocpp {

// Neo4j Admin
class Neo4jAdmin: public Neo4jInterface {
  Neo4jConnectionPool *pool = NULL;
  inline void initialize(const char * conn_str, bool secure, int conn_pool_size, \
    int pool_start_size, int pool_batch_size) {
      pool = new Neo4jConnectionPool(conn_pool_size, conn_str, secure, \
        pool_start_size, pool_batch_size);
  }

 public:
  // Initializers
  inline Neo4jAdmin(const char * conn_str, bool secure, int pool_size, \
    int pstart_size, int pbatch_size) {
    initialize(conn_str, secure, pool_size, pstart_size, pbatch_size);
  }

  inline Neo4jAdmin(std::string conn_str, bool secure, int pool_size, \
    int pstart_size, int pbatch_size) {
    initialize(conn_str.c_str(), secure, pool_size, pstart_size, pbatch_size);
  }

  inline Neo4jAdmin(const char * conn_str, bool secure, int pool_size) {
    initialize(conn_str, secure, pool_size, 0, 1);
  }

  inline Neo4jAdmin(std::string conn_str, bool secure, int pool_size) {
    initialize(conn_str.c_str(), secure, pool_size, 0, 1);
  }

  inline Neo4jAdmin(const char * conn_str, bool secure) {
    initialize(conn_str, secure, 5, 0, 1);
  }

  inline Neo4jAdmin(std::string conn_str, bool secure) {
    initialize(conn_str.c_str(), secure, 5, 0, 1);
  }

  inline Neo4jAdmin(const char * conn_str) {
    initialize(conn_str, false, 5, 0, 1);
  }

  inline Neo4jAdmin(std::string conn_str) {
    initialize(conn_str.c_str(), false, 5, 0, 1);
  }

  // Destructor
  ~Neo4jAdmin() {if (pool) {delete pool;}}

  // Query methods

  // Base Query
  inline ResultsIteratorInterface* execute(const char * query) {
    Neo4jQuerySession *qs = pool->get_connection();
    // Execute the query
    neo4j_result_stream_t *res = neo4j_run(qs->connection, query, neo4j_null);

    // Check for a failure
    int failure_check = neo4j_check_failure(res);
    if (failure_check != 0) {
      const struct neo4j_failure_details *fd;
      fd = neo4j_failure_details(res);
      pool->release_connection(qs);
      throw Neo4jException(fd->description, res);
    }

    // Return a results iterator for results access
    return new ResultsIterator(res, qs, pool);
  }

  // std::string query
  inline ResultsIteratorInterface* execute(std::string query) {
    return execute(query.c_str());
  }

  // Base Query with Parameters
  inline ResultsIteratorInterface* execute(const char * query, \
    std::unordered_map<std::string, \
    Neo4jQueryParameterInterface*> query_params) {
      // Get lists of keys and values for query parameters
      std::vector<std::string> keys;
      keys.reserve(query_params.size());

      std::vector<Neo4jQueryParameterInterface*> vals;
      vals.reserve(query_params.size());

      for (auto kv : query_params) {
        keys.push_back(kv.first);
        vals.push_back(kv.second);
      }

      // Create an array of neo4j map entries
      neo4j_map_entry_t map_entries[keys.size()];
      neo4j_value_t map_values[vals.size()];

      for (unsigned int i = 0; i < keys.size(); i++) {
        Neo4jQueryParameterInterface* val = vals[i];
        if (keys[i].empty()) {
          throw Neo4jException("query parameters cannot be null");
        }
        int val_type = val->get_type();
        if (val->is_array()) {
          // We have an array parameter
          // Insert the element into the map entry
          map_values[i] = val->get_neo4j_list();
        } else {
          // We have single value parameter, and just need to determine the type
          if (val_type == _BOOL_TYPE) {
            map_values[i] = neo4j_bool(val->get_boolean_value());
          } else if (val_type == _STR_TYPE) {
            const char * val_str = val->get_cstring_value();
            if (!val_str) {
              throw Neo4jException("query parameters must have length > 1.");
            } else {
              map_values[i] = neo4j_string(val->get_cstring_value());
            }
          } else if (val_type == _INT_TYPE) {
            map_values[i] = neo4j_int(val->get_integer_value());
          } else if (val_type == _FLT_TYPE) {
            map_values[i] = neo4j_float(val->get_double_value());
          }
        }
        map_entries[i] = neo4j_map_entry(keys[i].c_str(), map_values[i]);
      }

      // Create a neo4j value of the map
      neo4j_value_t param_map = neo4j_map(map_entries, keys.size());

      // Retrieve a database connection from the pool
      Neo4jQuerySession *qs = pool->get_connection();

      // Execute the query
      neo4j_result_stream_t *res = neo4j_run(qs->connection, query, param_map);

      // Check for a failure
      int failure_check = neo4j_check_failure(res);

      // If a failure is found
      if (failure_check != 0) {
        // Release the connection from the pool
        pool->release_connection(qs);

        // If our failure was related to the statement, then throw
        // a related exception
        if (failure_check == NEO4J_STATEMENT_EVALUATION_FAILED) {
          const struct neo4j_failure_details *fd;
          fd = neo4j_failure_details(res);
          if (fd && fd->description) {
            throw Neo4jException(fd->description, res);
          }
        }

        // If we weren't able to retrieve failure details, throw a general exception
        throw Neo4jException("Unknown error encountered running query", res);
      }

      // Return a results iterator for results access
      return new ResultsIterator(res, qs, pool);
  }

  // std::string query with parameters
  ResultsIteratorInterface* execute(std::string query, \
    std::unordered_map<std::string, \
    Neo4jQueryParameterInterface*> query_params) {
    return execute(query.c_str(), query_params);
  }
};

} // namespace Neocpp

#endif  // NEOCPP_CONNECTION_IMPL_NEO4J_ADMIN_H_
