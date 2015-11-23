<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\stream\StreamType;
use hhpack\process\descriptor\ReadDescriptor;
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
