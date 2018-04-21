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

// A slot pool is a thread-safe container for retrieving values from a fixed
// set of integers.  This is an internal component for any resource pool, such
// as a connection pool.

#ifndef NEOCPP_CONNECTION_IMPL_SLOT_POOL_H_
#define NEOCPP_CONNECTION_IMPL_SLOT_POOL_H_

#include <mutex>

namespace Neocpp {

class SlotPool {
  // Internal integers
  int connection_limit = 1;

  // Mutex for finding a next slot
  std::mutex get_slot_mutex;

  // Array of ints (0/1) which determine which connections are open vs closed
  int *slots;

 public:
  // Create a new Resource pool with the given limit
  inline SlotPool(int conn_limit) {
    connection_limit = conn_limit;
    slots = new int[connection_limit];
    for (int i = 0; i < connection_limit; i++) {
      slots[i] = 0;
    }
  }

  // Destroy the resource pool
  inline ~SlotPool() {
    delete[] slots;
  }

  // Retrieve the next available resource slot
  inline int find_next_slot() {
    // Get the mutex to ensure we get a unique connection
    std::lock_guard<std::mutex> lock(get_slot_mutex);

    // Find the next available connection slot
    // If none are available, wait until one is freed
    bool connection_found = false;
    while (!connection_found) {
      for (int j = 0; j < connection_limit; j++) {
        if (slots[j] == 0) {
          // slot is available
          slots[j] = 1;
          return j;
        }
      }
    }
    return -1;
  }

  // Release a slot
  inline void release_slot(int slot_index) {
    slots[slot_index] = 0;
  }
};

}  // namespace Neocpp
#endif  // NEOCPP_CONNECTION_IMPL_SLOT_POOL_H_
