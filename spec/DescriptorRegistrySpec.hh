<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\PipeType;
use hhpack\process\Descriptor;
use hhpack\process\DescriptorRegistry;

describe(DescriptorRegistry::class, function () {
  describe('toArray()', function () {
    beforeEach(function () {
      $this->registry = DescriptorRegistry::fromArray([
        new Descriptor(PipeType::Stdin, [ 'pipe', 'r' ]),
        new Descriptor(PipeType::Stdout, [ 'pipe', 'w' ]),
        new Descriptor(PipeType::Stderr, [ 'pipe', 'w' ])
      ]);
    });
    it('returns array value', function() {
      $result = $this->registry->toArray();
      expect($result[0])->toBe([ 'pipe', 'r' ]);
      expect($result[1])->toBe([ 'pipe', 'w' ]);
      expect($result[2])->toBe([ 'pipe', 'w' ]);
    });
  });
});
