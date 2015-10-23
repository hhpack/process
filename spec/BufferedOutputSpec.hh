<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\BufferedOutput;

describe(BufferedOutput::class, function () {
  beforeEach(function () {
    $this->output = new BufferedOutput();
  });
  describe('append()', function () {
    it('', function() {
      $this->output->append('text');
      expect((string) $this->output)->toBe('text');
    });
  });
});