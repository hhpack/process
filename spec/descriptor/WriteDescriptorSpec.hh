<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\StreamType;
use hhpack\process\descriptor\WriteDescriptor;

describe(WriteDescriptor::class, function () {
  describe('isReadDescriptor()', function () {
    beforeEach(function () {
      $this->descriptor = new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]);
    });
    it('returns false', function() {
      expect($this->descriptor->isReadDescriptor())->toBeFalse();
    });
  });

  describe('isWriteDescriptor()', function () {
    beforeEach(function () {
      $this->descriptor = new WriteDescriptor(StreamType::Stdin, ['pipe', 'r']);
    });
    it('returns true', function() {
      expect($this->descriptor->isWriteDescriptor())->toBeTrue();
    });
  });
});
