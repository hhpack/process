<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\output\OutputBufferedStream;

describe(OutputBufferedStream::class, function () {
  beforeEach(function () {
    $this->output = new OutputBufferedStream();
  });
  describe('write()', function () {
    it('write text', function() {
      $this->output->write('text');
      expect((string) $this->output)->toBe('text');
    });
  });
});
