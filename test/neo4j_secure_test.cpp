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

#include <assert.h>
#include <unistd.h>
#include <string>
#include <unordered_map>
#include <iostream>

#include "neocpp/connection/interface/neo4j_tls_config.h"
#include "neocpp/connection/interface/neo4j_interface.h"
#include "neocpp/connection/impl/libneo4j_factory.h"

#include "neocpp/data/interface/list_interface.h"
#include "neocpp/data/interface/map_interface.h"
#include "neocpp/data/interface/object_interface.h"
#include "neocpp/data/interface/query_parameter_interface.h"
#include "neocpp/data/interface/result_iterator_interface.h"
#include "neocpp/data/interface/result_tree_interface.h"

Neocpp::Neo4jInterface *neo = NULL;
Neocpp::LibNeo4jFactory *neo4j_factory = NULL;

int hello_world_test() {
  std::cout << "Running Hello World Test" << std::endl;
  // Execute a query
  Neocpp::ResultsIteratorInterface *results = NULL;
  std::string query = "RETURN 'hello world'";
  results = neo->execute(query);
  assert(results);

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  assert(result);
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;
  assert(result_string == "\"hello world\"");

  delete obj;
  delete result;
  delete results;
  return 0;
}

// Main Method
int main(int argc, char** argv) {
  // Get the component factory
  neo4j_factory = new Neocpp::LibNeo4jFactory;

  // Set up the TLS Configuration
  Neocpp::Neo4jTlsConfig *tls_conf = neo4j_factory->get_neo4j_tls_configuration();
  tls_conf->set_ca_file("/var/ssl/ca.crt");
  //tls_conf->set_key("/var/ssl/neo4j/server.key");
  //tls_conf->set_key_password("password");
  //tls_conf->set_known_hosts_file("known_hosts");
  //tls_conf->set_trust_known_hosts(true);

  // Start the Neo4j Administrator
  if (argc > 1) {
    std::string conn_str(argv[1]);
    std::cout << conn_str << std::endl;
    neo = neo4j_factory->get_neo4j_interface(conn_str, tls_conf);
  } else {
    neo = neo4j_factory->get_neo4j_interface("neo4j://localhost:7687", tls_conf);
  }

  int ret_val = hello_world_test();

  delete neo;
  delete tls_conf;
  delete neo4j_factory;

  return ret_val;
}
