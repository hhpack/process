<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\input\NullInputStream;
use hhpack\process\output\BufferedOutputStream;

describe(NullInputStream::class, function () {
  describe('read()', function () {
    beforeEach(function () {
      $this->input = new NullInputStream();
    });
    it('read text', function() {
      $output = $this->input->read();
      expect((string) $output)->toBe('');
    });
  });
  describe('close()', function () {
    beforeEach(function () {
      $this->input = new NullInputStream();
    });
    it('close stream', function() {
      expect($this->input->isOpened())->toBeTrue();
      expect($this->input->isClosed())->toBeFalse();

      $this->input->close();

      expect($this->input->isOpened())->toBeFalse();
      expect($this->input->isClosed())->toBeTrue();
    });
  });
});
