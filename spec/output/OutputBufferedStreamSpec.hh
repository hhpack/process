<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\output\OutputBufferedStream;

describe(OutputBufferedStream::class, function () {
  beforeEach(function () {
    $this->output = new OutputBufferedStream();
  });
  describe('append()', function () {
    it('append text', function() {
      $this->output->append('text');
      expect((string) $this->output)->toBe('text');
    });
  });
});
