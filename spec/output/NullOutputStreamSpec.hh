<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Output\NullOutputStream;

describe(NullOutputStream::class, function () {
  describe('write()', function () {
    beforeEach(function () {
      $this->output = new NullOutputStream();
    });
    it('write text', function() {
      $bytes = $this->output->write('text');
      expect($bytes)->toBe(4);
    });
  });
  describe('close()', function () {
    beforeEach(function () {
      $this->output = new NullOutputStream();
    });
    it('close stream', function() {
      expect($this->output->isOpened())->toBeTrue();
      expect($this->output->isClosed())->toBeFalse();

      $this->output->close();

      expect($this->output->isOpened())->toBeFalse();
      expect($this->output->isClosed())->toBeTrue();
    });
  });
});
