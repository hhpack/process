<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\StreamType;
use hhpack\process\descriptor\Descriptor;
use hhpack\process\descriptor\DescriptorRegistry;

describe(DescriptorRegistry::class, function () {
  describe('toArray()', function () {
    beforeEach(function () {
      $this->registry = DescriptorRegistry::fromArray([
        new Descriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
        new Descriptor(StreamType::Stdout, [ 'pipe', 'w' ]),
        new Descriptor(StreamType::Stderr, [ 'pipe', 'w' ])
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
