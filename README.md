# fast-native-fn

Provides a simple shortcut way to use `v8-fast-api-calls.h` without some of less
interesting boilerpate code.

It also stubs the usage on older Node.js versions, so your code will still
compile there. In those versions, the fast path will not be used.

> **Note:** This module is intended as a temporary measure, until `N-API` gets
> support for `v8-fast-api-calls.h`.

## Usage

First, make sure your `binding.gyp` adds the output of this module to the
`include_dirs`.

```
    "include_dirs": ["<!(node -e \"require('fast-native-fn')\")"]
```

Now, use the header in your binding file.

Remember the constraints for fast call functions:

* They must not allocate on the JS heap.
* They must not call into JS code.
* They (currently) can only return void.
* Only the following argument types are supported:
  * `bool`
  * `int32_t`
  * `uint32_t`
  * `int64_t`
  * `uint64_t`
  * `float32_t`
  * `float64_t`

```cpp
// binding.cc

/* include the header file */
#include <fast-native-fn.h>

/* define your native addon function as you normally would. */
void DoSomethingSlow(const FunctionCallbackInfo<Value>& args) {
  /* ... */
}

/* define the fast version of the function. note the constraints above. */
void DoSomethingFast(ApiObject receiver, int32_t arg0/*, ... */) {
  /* ... */
}

/* then in yout module's init function, use NODE_SET_FAST_METHOD instead of NODE_SET_METHOD */
NODE_SET_FAST_METHOD(
  exports,
  "doSomething",
  DoSomethingFast,
  DoSomethingSlow
  );
```

Make sure to run your code with `--turbo-fast-api-calls` to get enable the fast
paths.

## License

The MIT license. See LICENSE.txt.
