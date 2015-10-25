<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\PipeType;
use hhpack\process\FileDescriptor;
use hhpack\process\FileDescriptorRegistry;

describe(FileDescriptorRegistry::class, function () {
  describe('toArray()', function () {
    beforeEach(function () {
      $this->registry = FileDescriptorRegistry::fromArray([
        new FileDescriptor(PipeType::Stdin, [ 'pipe', 'r' ]),
        new FileDescriptor(PipeType::Stdout, [ 'pipe', 'w' ]),
        new FileDescriptor(PipeType::Stderr, [ 'pipe', 'w' ])
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
