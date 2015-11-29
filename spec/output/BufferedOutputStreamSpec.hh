<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\output\BufferedOutputStream;

describe(BufferedOutputStream::class, function () {
  beforeEach(function () {
    $this->output = new BufferedOutputStream();
  });
  describe('write()', function () {
    it('write text', function() {
      $this->output->write('text');
      expect((string) $this->output)->toBe('text');
    });
  });
});
