<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\input\StringInputStream;
use hhpack\process\output\OutputBufferedStream;

describe(StringInputStream::class, function () {
  describe('pipeTo()', function () {
    beforeEach(function () {
      $this->input = new StringInputStream('abcd');
      $this->output = new OutputBufferedStream();
      $this->input->pipeTo($this->output);
    });
    it('outputs the read data to output stream', function() {
      $this->input->read(1); //a
      expect($this->input->eof())->toBeFalse();

      $this->input->read(1); //b
      expect($this->input->eof())->toBeFalse();

      $this->input->read(1); //c
      expect($this->input->eof())->toBeFalse();

      $this->input->read(1); //d
      expect($this->input->eof())->toBeTrue();

      expect((string) $this->output)->toBe('abcd');

      $this->input->read(1); //empty
      expect($this->input->eof())->toBeTrue();
    });
  });

  describe('isOpen()', function () {
    beforeEach(function () {
      $this->input = new StringInputStream('abcd');
    });
    it('outputs the read data to output stream', function() {
      $this->input->read(1); //a
      expect($this->input->isOpened())->toBeTrue();

      $this->input->read(1); //b
      expect($this->input->isOpened())->toBeTrue();

      $this->input->read(1); //c
      expect($this->input->isOpened())->toBeTrue();

      $this->input->read(1); //d
      expect($this->input->isOpened())->toBeTrue();

      $this->input->read(1); //empty
      expect($this->input->isOpened())->toBeFalse();
    });
  });

});
