<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\input\InputStringStream;
use hhpack\process\output\BufferedOutput;

describe(InputStringStream::class, function () {
  describe('pipeTo()', function () {
    beforeEach(function () {
      $this->input = new InputStringStream('abcd');
      $this->output = new BufferedOutput();
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
      $this->input = new InputStringStream('abcd');
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
