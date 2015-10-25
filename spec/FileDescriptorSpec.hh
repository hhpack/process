<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\PipeType;
use hhpack\process\FileDescriptor;

describe(FileDescriptor::class, function () {
  describe('isReadDescriptor()', function () {
    context('when wrtie type', function() {
      beforeEach(function () {
        $this->descriptor = new FileDescriptor(PipeType::Stdin, ['pipe', 'r']);
      });
      it('returns false', function() {
        expect($this->descriptor->isReadDescriptor())->toBeFalse();
      });
    });
    context('when read type', function() {
      beforeEach(function () {
        $this->descriptor = new FileDescriptor(PipeType::Stdout, ['pipe', 'w']);
      });
      it('returns true', function() {
        expect($this->descriptor->isReadDescriptor())->toBeTrue();
      });
    });
  });

  describe('isWriteDescriptor()', function () {
    context('when wrtie type', function() {
      beforeEach(function () {
        $this->descriptor = new FileDescriptor(PipeType::Stdin, ['pipe', 'r']);
      });
      it('returns true', function() {
        expect($this->descriptor->isWriteDescriptor())->toBeTrue();
      });
    });
    context('when read type', function() {
      beforeEach(function () {
        $this->descriptor = new FileDescriptor(PipeType::Stdout, ['pipe', 'w']);
      });
      it('returns false', function() {
        expect($this->descriptor->isWriteDescriptor())->toBeFalse();
      });
    });
  });
});
