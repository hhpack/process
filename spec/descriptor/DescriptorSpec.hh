<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\StreamType;
use hhpack\process\descriptor\Descriptor;

describe(Descriptor::class, function () {
  describe('isReadDescriptor()', function () {
    context('when wrtie type', function() {
      beforeEach(function () {
        $this->descriptor = new Descriptor(StreamType::Stdin, ['pipe', 'r']);
      });
      it('returns false', function() {
        expect($this->descriptor->isReadDescriptor())->toBeFalse();
      });
    });
    context('when read type', function() {
      beforeEach(function () {
        $this->descriptor = new Descriptor(StreamType::Stdout, ['pipe', 'w']);
      });
      it('returns true', function() {
        expect($this->descriptor->isReadDescriptor())->toBeTrue();
      });
    });
  });

  describe('isWriteDescriptor()', function () {
    context('when wrtie type', function() {
      beforeEach(function () {
        $this->descriptor = new Descriptor(StreamType::Stdin, ['pipe', 'r']);
      });
      it('returns true', function() {
        expect($this->descriptor->isWriteDescriptor())->toBeTrue();
      });
    });
    context('when read type', function() {
      beforeEach(function () {
        $this->descriptor = new Descriptor(StreamType::Stdout, ['pipe', 'w']);
      });
      it('returns false', function() {
        expect($this->descriptor->isWriteDescriptor())->toBeFalse();
      });
    });
  });
});
