<?hh //partial

namespace hhpack\process\spec;

use hhpack\process\stream\StreamType;
use hhpack\process\descriptor\WriteDescriptor;
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
