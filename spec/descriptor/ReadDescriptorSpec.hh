<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\StreamType;
use hhpack\process\descriptor\ReadDescriptor;

describe(ReadDescriptor::class, function () {
  describe('isReadDescriptor()', function () {
    beforeEach(function () {
      $this->descriptor = new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ]);
    });
    it('returns true', function() {
      expect($this->descriptor->isReadDescriptor())->toBeTrue();
    });
  });

  describe('isWriteDescriptor()', function () {
    beforeEach(function () {
      $this->descriptor = new ReadDescriptor(StreamType::Stdout, ['pipe', 'w' ]);
    });
    it('returns false', function() {
      expect($this->descriptor->isWriteDescriptor())->toBeFalse();
    });
  });
});
