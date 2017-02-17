<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\WriteDescriptor;
use LogicException;

describe(WriteDescriptor::class, function () {
  describe('__construct()', function () {
    context('when unsupport type', function () {
      it('throw LogicException', function() {
        expect(function () {
          $descriptor = new WriteDescriptor(StreamType::Stdout, [ 'pipe', 'r' ]);
        })->toThrow(LogicException::class);
      });
    });
  });
});
