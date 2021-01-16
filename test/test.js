'use strict';

const assert = require('assert');
const binding = require('./build/Release/test.node');

const resultBuf = Buffer.alloc(4);
binding.setResultBuffer(resultBuf);
const resultInt32 = new Int32Array(resultBuf.buffer, resultBuf.offset, 1);

function addFast (a, b) {
  binding.addFast(a, b);
  return resultInt32[0];
}

function addSlow (a, b) {
  binding.addSlow(a, b);
  return resultInt32[0];
}

assert.strictEqual(5, addFast(2, 3));
assert.strictEqual(7, addSlow(3, 4));

console.log('basic test passed');

if (Number(process.versions.node.split('.')[0]) >= 15) {
  const { execSync } = require('child_process');
  const { join } = require('path');
  execSync(`node --turbo-fast-api-calls ${join(__dirname, 'test-fast-path.js')}`);
  console.log('fast path passed');
} else {
  console.log('fast path skipped (not supported on this node version)');
}
