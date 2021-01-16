{
  "targets": [{
    "target_name" : "test",
    "defines": [ "V8_DEPRECATION_WARNINGS=1" ],
    "sources"     : [ "test.cpp" ],
    "include_dirs": ["<!(node -e \"require('..')\")"]
  }]
}
