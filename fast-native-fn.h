#if NODE_MAJOR_VERSION > 14

#include <v8-fast-api-calls.h>

template <typename F>
void NODE_SET_FAST_METHOD(v8::Local<v8::Object> exports, const char * name, F* fastFunc, v8::FunctionCallback slowFunc) {
  v8::Isolate * isolate = exports->GetIsolate();
  v8::CFunction fastCFunc = v8::CFunction::Make(fastFunc);
  v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(
      isolate,
      slowFunc,
      v8::Local<v8::Value>(),
      v8::Local<v8::Signature>(),
      0,
      v8::ConstructorBehavior::kThrow,
      v8::SideEffectType::kHasSideEffect,
      &fastCFunc
      );
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  exports->Set(
      context,
      v8::String::NewFromUtf8(isolate, name).ToLocalChecked(),
      funcTemplate->GetFunction(context).ToLocalChecked()
      );
}

#else

#include <stdint.h>

/* We're defining this here for older versions of Node.js, so that they still compile. */
namespace v8 {
  struct ApiObject {
    uintptr_t address;
  };
}

#define NODE_SET_FAST_METHOD(exports, name, fast, slow) \
  NODE_SET_METHOD(exports, name, slow)

#endif
