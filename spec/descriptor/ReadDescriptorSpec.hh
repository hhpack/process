<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\ReadDescriptor;
use LogicException;

describe(ReadDescriptor::class, function () {
  describe('__construct()', function () {
    context('when unsupport type', function () {
      it('throw LogicException', function() {
        expect(function () {
          $descriptor = new ReadDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]);
        })->toThrow(LogicException::class);
      });
    });
  });
});
