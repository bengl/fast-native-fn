#include <node.h>
#include <node_buffer.h>
#include <fast-native-fn.h>
#include <stdint.h>
#include <iostream>

using namespace v8;

namespace test {

  int32_t * result;

  void add(int32_t a, int32_t b) {
    *result = a + b;
  }

  void AddSlow(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> ctx = isolate->GetCurrentContext();

    int32_t a = args[0]->IntegerValue(ctx).FromJust();
    int32_t b = args[1]->IntegerValue(ctx).FromJust();

    add(a, b);
  }

  void AddFast(ApiObject receiver, int32_t a, int32_t b) {
    add(a, b + 2);
  }

  void SetResultBuffer(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> ctx = isolate->GetCurrentContext();
    result = (int32_t *)node::Buffer::Data(args[0]->ToObject(ctx).ToLocalChecked());
  }

  void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "addSlow", AddSlow);
    NODE_SET_FAST_METHOD(exports, "addFast", AddFast, AddSlow);
    NODE_SET_METHOD(exports, "setResultBuffer", SetResultBuffer);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
}
