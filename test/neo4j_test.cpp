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
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;
  assert(result_string == "\"hello world\"");

  delete obj;
  delete result;
  delete results;
  return 0;
}

int creation_test() {
  std::cout << "Running Object Creation Test" << std::endl;
  // Execute the query
  std::string query = \
    "CREATE (you:Person {name:'EA', list: [1, 2, 3]}) RETURN you";
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query);
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "EA");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results;
  return 0;
}

int match_test() {
  std::cout << "Running Object Retrieval Test" << std::endl;
  // Execute the query
  std::string query = \
    "MATCH (you:Person) WHERE you.name = 'EA' RETURN you";
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query);
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "EA");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results;
  return 0;
}

int match_create_test() {
  std::cout << "Running Object Match Create Test" << std::endl;
  // Execute the query
  std::string query = \
    "MATCH (you:Person {name:'EA'}) CREATE (you)-[like:LIKE]->(neo:Database "
    "{name:'Neo4j', list: [4, 5, 6]}) RETURN you, like, neo";
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query);
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  Neocpp::DbObjectInterface *edge = result->get(1);
  Neocpp::DbObjectInterface *db_obj = result->get(2);

  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;
  std::string result_string2 = edge->to_string();
  std::cout << result_string2 << std::endl;
  std::string result_string3 = db_obj->to_string();
  std::cout << result_string3 << std::endl;

  assert(obj->is_node());
  assert(db_obj->is_node());

  assert(edge->is_edge());
  assert(edge->type() == "LIKE");

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");
  Neocpp::DbListInterface *label_list2 = db_obj->labels();
  assert(label_list2->get_string_element(0) == "Database");

  // Test the properties coming back off the Person object
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "EA");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  // Test the properties coming back off the Database object
  Neocpp::DbMapInterface *map2 = db_obj->properties();
  std::cout << map2->to_string() << std::endl;

  assert(map2->element_exists("name"));
  assert(map2->get_string_element("name") == "Neo4j");
  assert(map2->element_exists("list"));

  Neocpp::DbListInterface *list_prop2 = map2->get_list_element("list");
  assert(list_prop2->size() == 3);
  assert(list_prop2->get_int_element(0) == 4);
  assert(list_prop2->get_int_element(1) == 5);
  assert(list_prop2->get_int_element(2) == 6);

  delete list_prop2;
  delete map2;
  delete list_prop;
  delete map;
  delete label_list;
  delete label_list2;
  delete obj;
  delete edge;
  delete db_obj;
  delete result;
  delete results;
  return 0;
}

int bad_query_test() {
  std::cout << "Running Bad Query Test" << std::endl;
  std::string query = "MATCH (you:Person {name:'EA'}) "
    "CREATE (you)-[like:LIKE]->(neo:Database {name:'Neo4j', list: [1, 2, 3]) "
    "RETURN you, like, neo";

  Neocpp::ResultsIteratorInterface *results = NULL;
  try {
    results = neo->execute(query);
    assert(false);
  }
  catch(std::exception& e) {
    std::cout << "Error running Query: " << e.what() << std::endl;
  }

  if (results) {delete results;}
  return 0;
}

int int_query_parameter_test() {
  std::cout << "Running Integer Query Parameter Test" << std::endl;
  // Set up some data to use
  std::string setup_query = \
    "CREATE (you:Gelatin {name:1, list: [1, 2, 3]}) RETURN you";
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(setup_query);
  if (!results) return -1;
  delete results;

  // Set up the query parameter and query
  std::cout << "Query Setup" << std::endl;
  std::unordered_map<std::string, Neocpp::Neo4jQueryParameterInterface*> query_params1;
  Neocpp::Neo4jQueryParameterInterface *name_param = \
    neo4j_factory->get_neo4j_query_parameter(1);
  query_params1.emplace("inp_name", name_param);
  std::string param_query = \
    "MATCH (you:Gelatin) WHERE you.name = {inp_name} RETURN you";

  // Run the query
  std::cout << "Query Execution" << std::endl;
  Neocpp::ResultsIteratorInterface *results2 = NULL;
  results2 = neo->execute(param_query, query_params1);
  if (!results2) return -1;

  // Access the results
  std::cout << "Accessing Results" << std::endl;
  Neocpp::ResultTreeInterface *result = results2->next();
  if (!result) assert(false);
  Neocpp::DbObjectInterface *obj = result->get(0);
  if (!obj) assert(false);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Gelatin");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_int_element("name") == 1);
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results2;
  delete name_param;
  return 0;
}

int string_query_parameter_test() {
  std::cout << "Running String Query Parameter Test" << std::endl;
  std::unordered_map<std::string, Neocpp::Neo4jQueryParameterInterface*> query_params2;
  Neocpp::Neo4jQueryParameterInterface *name_param2 = \
    neo4j_factory->get_neo4j_query_parameter("EA");
  query_params2.emplace("inp_name", name_param2);
  std::string query = \
    "MATCH (you:Person) WHERE you.name = {inp_name} RETURN you";

  // Run the query
  std::cout << "Query Execution" << std::endl;
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query, query_params2);
  if (!results) return -1;

  // Access the results
  std::cout << "Accessing Results" << std::endl;
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "EA");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results;
  delete name_param2;
  return 0;
}

int path_test() {
  std::cout << "Path Test" << std::endl;
  std::cout << "Data Setup" << std::endl;
  // Setup data for the path test
  std::string setup_query1 = \
    "CREATE (base:CoordinateSystem {name: '1', list: [7, 8, 9]}) RETURN base";
  std::string setup_query2 = \
    "MATCH (base:CoordinateSystem {name: '1'}) "
    "CREATE (base)-[transform:Transform {matrix: "
    "[1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1]}]->(next:CoordinateSystem "
    "{name: '2', list: [10, 11, 12]}) "
    "RETURN next";
  std::string setup_query3 = \
    "MATCH (base:CoordinateSystem {name: "
    "'1'})-[transform:Transform]->(next:CoordinateSystem {name: '2'}) "
    "CREATE (next)-[nexttransform:Transform {matrix: "
    "[1,1,0,1,0,1,0,1,1,0,1,1,0,0,0,1]}]->(final:CoordinateSystem "
    "{name: '3', list: [1, 2, 3]}) "
    "RETURN final";

  Neocpp::ResultsIteratorInterface *setup_results1 = NULL;
  Neocpp::ResultsIteratorInterface *setup_results2 = NULL;
  Neocpp::ResultsIteratorInterface *setup_results3 = NULL;

  setup_results1 = neo->execute(setup_query1);
  if (!setup_results1) return -1;
  Neocpp::ResultTreeInterface *setup_result1 = setup_results1->next();
  if (!setup_result1) assert(false);
  Neocpp::DbObjectInterface *first_obj = setup_result1->get(0);
  assert(first_obj->is_node());
  delete first_obj;
  delete setup_result1;
  delete setup_results1;

  setup_results2 = neo->execute(setup_query2);
  if (!setup_results2) return -1;
  Neocpp::ResultTreeInterface *setup_result2 = setup_results2->next();
  if (!setup_result2) assert(false);
  Neocpp::DbObjectInterface *second_obj = setup_result2->get(0);
  assert(second_obj->is_node());
  delete second_obj;
  delete setup_result2;
  delete setup_results2;

  setup_results3 = neo->execute(setup_query3);
  if (!setup_results3) return -1;
  Neocpp::ResultTreeInterface *setup_result3 = setup_results3->next();
  if (!setup_result3) assert(false);
  Neocpp::DbObjectInterface *third_obj = setup_result3->get(0);
  assert(third_obj->is_node());
  delete third_obj;
  delete setup_result3;
  delete setup_results3;

  // Actual Path Tests
  std::cout << "Query Execution" << std::endl;
  std::string query = \
    "MATCH (base:CoordinateSystem {name:'1'}), (next:CoordinateSystem "
    "{name:'3'}), p = shortestPath((base)-[r*]-(next)) RETURN p";
  Neocpp::ResultsIteratorInterface *results = neo->execute(query);
  if (!results) return -1;

  // Access the results
  std::cout << "Access Results" << std::endl;
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) assert(false);
  Neocpp::DbObjectInterface *path = result->get(0);
  std::cout << "Object Retrieved" << std::endl;
  assert(path->is_path());
  assert(path->size() == 5);
  for (int i = 0; i < 5; i++) {
    Neocpp::DbObjectInterface *path_obj = path->get_path_element(i);
    std::cout << path_obj->to_string() << std::endl;
    // Generic Tests
    if (i % 2 == 0) {
      std::cout << "Testing Node " << i << std::endl;
      assert(path_obj->is_node());
      Neocpp::DbListInterface *label_list = path_obj->labels();
      assert(label_list->get_string_element(0) == "CoordinateSystem");
      delete label_list;
    } else {
      std::cout << "Testing Edge " << i << std::endl;
      assert(path_obj->is_edge());
      assert(path_obj->type() == "Transform");
      assert(path_obj->forward());
    }
    // Properties Tests
    Neocpp::DbMapInterface *map = path_obj->properties();
    if (i == 0) {
      assert(map->element_exists("name"));
      assert(map->get_string_element("name") == "1");
    } else if (i == 2) {
      assert(map->element_exists("name"));
      assert(map->get_string_element("name") == "2");
    } else if (i == 4) {
      assert(map->element_exists("name"));
      assert(map->get_string_element("name") == "3");
    }
    delete map;
    delete path_obj;
  }

  delete path;
  delete result;
  delete results;
  return 0;
}

int int_list_parameter_test() {
  std::cout << "Running Integer List Parameter Test" << std::endl;
  // Setup the query
  std::string query = \
    "CREATE (you:Person {name:'GummyBear', list: {list_vals}}) RETURN you";
  std::unordered_map<std::string, Neocpp::Neo4jQueryParameterInterface*> query_params;
  Neocpp::Neo4jQueryParameterInterface *list_vals_parameter = \
    neo4j_factory->get_neo4j_query_parameter();
  list_vals_parameter->add_value(1);
  list_vals_parameter->add_value(2);
  list_vals_parameter->add_value(3);
  query_params.emplace("list_vals", list_vals_parameter);

  // Execute the query
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query, query_params);
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "GummyBear");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_int_element(0) == 1);
  assert(list_prop->get_int_element(1) == 2);
  assert(list_prop->get_int_element(2) == 3);

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results;
  delete list_vals_parameter;
  return 0;
}

int string_list_parameter_test() {
  std::cout << "Running String List Parameter Test" << std::endl;
  // Setup the query
  std::string query = \
    "CREATE (you:Person {name:'JellyBean', list: {list_vals}}) RETURN you";
  std::unordered_map<std::string, Neocpp::Neo4jQueryParameterInterface*> query_params;
  Neocpp::Neo4jQueryParameterInterface *list_vals_parameter = \
    neo4j_factory->get_neo4j_query_parameter();
  std::string param_val1 = "ABCD";
  std::string param_val2 = "GHIJKL";
  std::string param_val3 = "MNOPQRST";
  list_vals_parameter->add_value(param_val1);
  list_vals_parameter->add_value(param_val2);
  list_vals_parameter->add_value(param_val3);
  query_params.emplace("list_vals", list_vals_parameter);

  // Execute the query
  Neocpp::ResultsIteratorInterface *results = NULL;
  results = neo->execute(query, query_params);
  if (!results) return -1;

  // Access the results
  Neocpp::ResultTreeInterface *result = results->next();
  if (!result) return -1;
  Neocpp::DbObjectInterface *obj = result->get(0);
  std::string result_string = obj->to_string();
  std::cout << result_string << std::endl;

  assert(obj->is_node());

  // Labels
  Neocpp::DbListInterface *label_list = obj->labels();
  assert(label_list->get_string_element(0) == "Person");

  // Properties
  Neocpp::DbMapInterface *map = obj->properties();
  std::cout << map->to_string() << std::endl;

  assert(map->element_exists("name"));
  assert(map->get_string_element("name") == "JellyBean");
  assert(map->element_exists("list"));

  Neocpp::DbListInterface *list_prop = map->get_list_element("list");
  assert(list_prop->size() == 3);
  assert(list_prop->get_string_element(0) == "ABCD");
  assert(list_prop->get_string_element(1) == "GHIJKL");
  assert(list_prop->get_string_element(2) == "MNOPQRST");

  delete list_prop;
  delete map;
  delete label_list;
  delete obj;
  delete result;
  delete results;
  delete list_vals_parameter;
  return 0;
}

int run_tests() {
  if (hello_world_test() != 0) return -1;
  if (creation_test() != 0) return -1;
  if (match_test() != 0) return -1;
  if (match_create_test() != 0) return -1;
  if (bad_query_test() != 0) return -1;
  if (int_query_parameter_test() != 0) return -1;
  if (string_query_parameter_test() != 0) return -1;
  if (path_test() != 0) return -1;
  if (int_list_parameter_test() != 0) return -1;
  if (string_list_parameter_test() != 0) return -1;
  return 0;
}

// Main Method
int main(int argc, char** argv) {
  // Get the component factory
  neo4j_factory = new Neocpp::LibNeo4jFactory;

  // Start the Neo4j Administrator
  if (argc > 1) {
    std::string conn_str(argv[1]);
    std::cout << conn_str << std::endl;
    neo = neo4j_factory->get_neo4j_interface(conn_str);
  } else {
    neo = neo4j_factory->get_neo4j_interface("neo4j://localhost:7687");
  }

  int ret_val = run_tests();

  delete neo;
  delete neo4j_factory;

  return ret_val;
}
