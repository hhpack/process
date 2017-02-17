<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Output\BufferedOutputStream;

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
