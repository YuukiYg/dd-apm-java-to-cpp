# dd-apm-java-to-cpp

## Overview
This application is a sample for calling C++ shared library from Java, and monitoring APM using Datadog.
**An Incomplete point of this code** is, generating a Trace in Java, then generating Spans as children of the Trace in C++ which was called from Java.

## Before running application...

* Confirm Datadog Agent is running on your environment.

* Install dd-java-agent.jar
  * https://docs.datadoghq.com/ja/tracing/setup/java/?tab=springboot

* Set environment variables
  * DD_LOGS_INJECTION=true
  * DATADOG_API_KEY=your_api_key
  * DD_HOSTNAME=your_dd_hostname
  * DD_HOSTPORT=your_dd_hostport
  * LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/
  * DD_APM_ENABLED=true
* Compile C++
  * make
    ```
    get_latest_release() {wget -qO- "https://api.github.com/repos/$1/releases/latest" | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/';} && \
    VERSION="$(get_latest_release DataDog/dd-opentracing-cpp)" && \
    wget https://github.com/DataDog/dd-opentracing-cpp/archive/${VERSION}.tar.gz -O dd-opentracing-cpp.tar.gz && \
    mkdir -p dd-opentracing-cpp/.build && \
    tar zxvf dd-opentracing-cpp.tar.gz -C ./dd-opentracing-cpp/ --strip-components=1 && \
    cd dd-opentracing-cpp/.build && \
    # Download and install the correct version of opentracing-cpp, & other deps.
    ../scripts/install_dependencies.sh && \
    cmake .. && \
    make && \
    sudo make install
    ```
  * `sudo ldconfig`
  * `gcc -shared -fPIC -std=c++14 -o libplus.so  plus.cpp -I../deps/include -L../deps/lib/ -ldd_opentracing -lopentracing`
* Compile Java
  * `mvn install -Dmaven.test.skip=true`
    * Confirm $PATH points to Java11 for compiling using mvn.
 
## How to Run   
  * Run
    * `java -javaagent:/path/to/dd-java-agent.jar -jar java2cpp-0.0.1-SNAPSHOT.jar`
  * Access your app.
    * Send GET request to `http://YOUR_SERVER_ADDRESS:18002/test`
