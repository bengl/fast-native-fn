'use strict';

const binding = require('./build/Release/test.node');

const resultBuf = Buffer.alloc(4);
binding.setResultBuffer(resultBuf);
const resultInt32 = new Int32Array(resultBuf.buffer, resultBuf.offset, 1);

function addFast (a, b) {
  binding.addFast(a, b);
  return resultInt32[0];
}

// We run this 10k times, so that at some point optimization happens, putting us on the fast path.
for (let i = 0; i < 10000; i++) {
  const result = addFast(2, 3);
  if (result === 7) {
    process.exit(0);
  } else {
    console.log(result);
  }
}

throw new Error('did not optimize');
