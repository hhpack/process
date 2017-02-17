<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\WriteDescriptor;
use HHPack\Process\Descriptor\ReadDescriptor;
use HHPack\Process\Descriptor\DefaultDescriptorRegistry;

describe(DefaultDescriptorRegistry::class, function () {
  describe('toArray()', function () {
    beforeEach(function () {
      $this->registry = new DefaultDescriptorRegistry(
        new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
        new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ]),
        new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ])
      );
    });
    it('returns array value', function() {
      $result = $this->registry->toArray();
      expect($result[0])->toBe([ 'pipe', 'r' ]);
      expect($result[1])->toBe([ 'pipe', 'w' ]);
      expect($result[2])->toBe([ 'pipe', 'w' ]);
    });
  });
});
