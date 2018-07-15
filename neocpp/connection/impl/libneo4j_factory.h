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
#include "neocpp/connection/interface/neo4j_interface.h"
#include "neocpp/connection/interface/neo4j_tls_config.h"
#include "neocpp/connection/impl/neo4j_admin.h"
#include "neocpp/data/interface/query_parameter_interface.h"
#include "neocpp/data/impl/neo4j_query_parameter.h"

#ifndef NEOCPP_CONNECTION_INTERFACE_LIBNEO4J_FACTORY_H_
#define NEOCPP_CONNECTION_INTERFACE_LIBNEO4J_FACTORY_H_

namespace Neocpp {

//! The libneo4j-client Factory

//! The libneo4j-client factory exposes an implementation
//! of the neocpp interfaces which depends on libneo4j-client
//! https://github.com/cleishm/libneo4j-client
class LibNeo4jFactory {
 public:
  //! Create a new Service Component Factory
  LibNeo4jFactory() {}

  //! Delete a Service Component Factory
  ~LibNeo4jFactory() {}

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_string) {
    return new Neo4jAdmin(conn_string);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_string) {
    return new Neo4jAdmin(conn_string);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_str, \
    int pool_size) {
    return new Neo4jAdmin(conn_str, pool_size);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_str, \
    int pool_size) {
    return new Neo4jAdmin(conn_str, pool_size);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_str, \
    int pool_size, int pstart_size, int pbatch) {
    return new Neo4jAdmin(conn_str, pool_size, pstart_size, pbatch);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_str, \
    int pool_size, int pstart_size, int pbatch) {
    return new Neo4jAdmin(conn_str, pool_size, pstart_size, pbatch);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_string, \
      Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_string, tls_config);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_string, \
      Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_string, tls_config);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_str, \
    int pool_size, Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_str, pool_size, tls_config);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_str, \
    int pool_size, Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_str, pool_size, tls_config);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(const char * conn_str, \
    int pool_size, int pstart_size, int pbatch, Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_str, pool_size, pstart_size, pbatch, tls_config);
  }

  //! Get a Neo4j Interface instance
  inline Neo4jInterface* get_neo4j_interface(std::string conn_str, \
    int pool_size, int pstart_size, int pbatch, Neo4jTlsConfig *tls_config) {
    return new Neo4jAdmin(conn_str, pool_size, pstart_size, pbatch, tls_config);
  }

  //! Get a Neo4j Array Query Parameter
  inline Neo4jQueryParameterInterface* get_neo4j_query_parameter() {
    return new Neo4jQueryParameter();
  }

  //! Get a Neo4j Query Parameter
  inline Neo4jQueryParameterInterface* \
    get_neo4j_query_parameter(bool inp_bool) {
    return new Neo4jQueryParameter(inp_bool);
  }

  //! Get a Neo4j Query Parameter
  inline Neo4jQueryParameterInterface* \
    get_neo4j_query_parameter(std::string inp_str) {
    return new Neo4jQueryParameter(inp_str);
  }

  //! Get a Neo4j Query Parameter
  inline Neo4jQueryParameterInterface* \
    get_neo4j_query_parameter(const char * inp_str) {
    return new Neo4jQueryParameter(inp_str);
  }

  //! Get a Neo4j Query Parameter
  inline Neo4jQueryParameterInterface* get_neo4j_query_parameter(int inp_int) {
    return new Neo4jQueryParameter(inp_int);
  }

  //! Get a Neo4j Query Parameter
  inline Neo4jQueryParameterInterface* \
    get_neo4j_query_parameter(double inp_double) {
    return new Neo4jQueryParameter(inp_double);
  }

  //! Get a TLS Configuration Object

  //! We can pass this back with configuration data to intialize a
  //! secure socket
  inline Neo4jTlsConfig* get_neo4j_tls_configuration() {
    return new Neo4jTlsConfig();
  }
};

} // namespace Neocpp

#endif  // NEOCPP_CONNECTION_INTERFACE_LIBNEO4J_FACTORY_H_
