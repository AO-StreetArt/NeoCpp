We love pull requests from everyone.

Start by forking and cloning the repository, then execute the build_deps.sh script at scripts/linux/deb/build_deps.sh for Debian-based systems, and scripts/linux/rhel/build_deps.sh for RHEL/CentOS.

Make your changes and write tests for your changes, then ensure that all tests pass (against an active, unsecured Neo4j instance):

`make clean && make tests && cd test && ./neo4j_test`

Push to your fork and submit a pull request.

At this point you're waiting on us. We like to at least comment on pull requests within three business days (and, typically, one business day). We may suggest some changes or improvements or alternatives.

Some things that will increase the chance that your pull request is accepted:

* Write tests
* Comment your code
* Write a good commit message
* If you have many different commits, use rebase to consolidate down to a single commit
* Use [CppLint](https://github.com/google/styleguide/tree/gh-pages/cpplint) and follow the [Google C++ Style Guide](https://github.com/google/styleguide) wherever possible
