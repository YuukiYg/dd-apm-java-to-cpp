#include <datadog/opentracing.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

// externがないと、Javaから呼べなかった
extern "C" int plus(int m, int n);

int plus(int m, int n) {

  char *strenv;
  char dd_hostname[256];
  char dd_hostport[8];
  unsigned int dd_hostport_int;

  // 環境変数からAgentのHostnameを取得する。取得できない場合、"localhost" をデフォルトとして設定する。
  if ((strenv = getenv("DD_AGENT_HOST")) != NULL) {
    strcat(dd_hostname, strenv);
  }else{
    strcat(dd_hostname, "localhost");
  }

  // 環境変数からAgentのHostportを取得する。取得できない場合、8126をデフォルトとして設定する
  if((strenv = getenv("DD_AGENT_PORT")) != NULL){
    strcat(dd_hostport, strenv);
  }else{
    strcat(dd_hostport, "8126");
  }
  dd_hostport_int = atoi(dd_hostport);

  printf("dd_host:%s:%d\n", dd_hostname, dd_hostport_int);
  datadog::opentracing::TracerOptions tracer_options{dd_hostname, dd_hostport_int, "CppPLUS"};
  auto tracer = datadog::opentracing::makeTracer(tracer_options);

  // Create some spans.
  {
    auto span_a = tracer->StartSpan("A-plus");
    span_a->SetTag("tag", 123);
    auto span_b = tracer->StartSpan("B-plus", {opentracing::ChildOf(&span_a->context())});
    span_b->SetTag("tag", "value");
  }

  tracer->Close();

  printf("this log is from c++!\n");
  fflush(stdout);
  return m+n;
}

