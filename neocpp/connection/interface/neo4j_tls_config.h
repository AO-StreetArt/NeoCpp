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
#include <iostream>
#include <neo4j-client.h>

#ifndef NEOCPP_CONNECTION_INTERFACE_NEO4J_TLS_CONFIG_H_
#define NEOCPP_CONNECTION_INTERFACE_NEO4J_TLS_CONFIG_H_

namespace Neocpp {

inline int host_verification(void *userdata, const char *host, const char *fingerprint,
    neo4j_unverified_host_reason_t reason) {
  std::cout << "Trusting new fingerprint: " << fingerprint << std::endl;
  return NEO4J_HOST_VERIFICATION_TRUST;
}

//! Neo4j TLS Configuration Object

//! Stores certificate/key/ca/etc information for TLS encryption
class Neo4jTlsConfig {
  std::string ca_file;
  std::string ca_dir;
  std::string key;
  std::string key_password;
  // -1 is unset
  // 0 is true
  // 1 is false
  int trust_known_hosts = -1;
  std::string known_hosts_file;
 public:
   //! Constructor
   Neo4jTlsConfig() {}
   //! Destructor
  ~Neo4jTlsConfig() {}

  // CA File
  //! Update the CA File location
  inline void set_ca_file(std::string& new_file) {
    ca_file.assign(new_file);
  }
  //! Update the CA File location
  inline void set_ca_file(const char * new_file) {
    ca_file.assign(new_file);
  }
  //! Get the CA File location
  inline std::string get_ca_file() {
    return ca_file;
  }

  // CA Directory
  //! Update the CA Directory location
  inline void set_ca_dir(std::string& new_dir) {
    ca_dir.assign(new_dir);
  }
  //! Update the CA Directory location
  inline void set_ca_dir(const char * new_dir) {
    ca_dir.assign(new_dir);
  }
  //! Get the CA Directory location
  inline std::string get_ca_dir() {
    return ca_dir;
  }

  // Key File
  //! Update the Key file location
  inline void set_key(std::string& new_key) {
    key.assign(new_key);
  }
  //! Update the Key file location
  inline void set_key(const char * new_key) {
    key.assign(new_key);
  }
  //! Get the Key file location
  inline std::string get_key() {
    return key;
  }

  // Key Password File
  //! Update the Key password
  inline void set_key_password(std::string& new_pw) {
    key_password.assign(new_pw);
  }
  //! Update the Key password
  inline void set_key_password(const char * new_pw) {
    key_password.assign(new_pw);
  }
  //! Get the Key password
  inline std::string get_key_password() {
    return key_password;
  }

  // Known Hosts File
  //! Update the Known hosts file location
  inline void set_known_hosts_file(std::string& new_file) {
    known_hosts_file.assign(new_file);
  }
  //! Update the Known hosts file location
  inline void set_known_hosts_file(const char * new_file) {
    known_hosts_file.assign(new_file);
  }
  //! Get the Known hosts file location
  inline std::string get_known_hosts_file() {
    return known_hosts_file;
  }

  // Trust known hosts
  //! Set whether or not we trust known hosts
  inline void set_trust_known_hosts(bool new_value) {
    if (new_value) {
      trust_known_hosts = 0;
    } else {
      trust_known_hosts = 1;
    }
  }
  //! Get whether or not we trust known hosts
  inline bool get_trust_known_hosts() {
    if (trust_known_hosts == 0) {
      return true;
    }
    return false;
  }
  //! Get whether or not we have set a policy on trusting known hosts
  inline bool is_trust_known_hosts_set() {
    if (trust_known_hosts == -1) {
      return true;
    }
    return false;
  }
};

} // namespace Neocpp

#endif  // NEOCPP_CONNECTION_INTERFACE_NEO4J_TLS_CONFIG_H_
