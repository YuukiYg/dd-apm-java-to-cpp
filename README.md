# dd-apm-java-to-cpp

## Overview
This application is a sample for calling C++ shared library from Java, and monitoring APM using Datadog.
**An Incomplete point of this code** is, generating a Trace in Java, then generating Spans as children of the Trace in C++ which was called from Java.

## Before running application...

* Confirm Datadog Agent is running on your environment.

* Install dd-java-agent.jar
  * https://docs.datadoghq.com/ja/tracing/setup/java/?tab=springboot

* Generate shared library by compiling C++ code.
  * `gcc -shared -o libplus.so src/main/cpp/plus.cpp` for Linux
  * `gcc -shared -o plus.dll src\main\cpp\plus.cpp` for Windows
  * `gcc -shared -o libplus.dylib src/main/cpp/plus.cpp` for Mac

* Set environment variables
  * DD_LOGS_INJECTION=true
  * DATADOG_API_KEY=your_api_key

## How to Run
  * Compile
    * `mvn install -Dmaven.test.skip=true`
  * Run
    * `java -javaagent:/path/to/dd-java-agent.jar -jar java2cpp-0.0.1-SNAPSHOT.jar`
  * Access your app.
    * Send GET request to `http://YOUR_SERVER_ADDRESS:18002/test`
