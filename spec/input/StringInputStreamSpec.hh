<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\input\StringInputStream;
use hhpack\process\output\BufferedOutputStream;

describe(StringInputStream::class, function () {
  describe('read()', function () {
    beforeEach(function () {
      $this->input = new StringInputStream('abcd');
    });
    it('returns readed all data', function() {
      expect($this->input->eof())->toBeFalse();
      $input = $this->input->read(1);
      expect($this->input->eof())->toBeTrue();
      expect($input)->toBe('abcd');
    });
  });

  describe('isClosed()', function () {
    beforeEach(function () {
      $this->input = new StringInputStream('abcd');
    });
    context('when opened', function () {
      it('returns false', function() {
        expect($this->input->isClosed())->toBeFalse();
      });
    });
    context('when closed', function () {
      it('returns true', function() {
        $this->input->close();
        expect($this->input->isClosed())->toBeTrue();
      });
    });
  });

});
