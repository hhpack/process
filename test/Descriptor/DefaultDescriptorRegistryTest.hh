<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\{ WriteDescriptor, ReadDescriptor, DefaultDescriptorRegistry };
use HackPack\HackUnit\Contract\Assert;

final class DefaultDescriptorRegistryTest
{
    <<Test>>
    public function toArray(Assert $assert) : void
    {
        $registry = new DefaultDescriptorRegistry(
            new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
            new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ]),
            new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ])
        );
        $result = $registry->toArray();

        $assert->string($result[0][0])->is('pipe');
        $assert->string($result[0][1])->is('r');

        $assert->string($result[1][0])->is('pipe');
        $assert->string($result[1][1])->is('w');

        $assert->string($result[2][0])->is('pipe');
        $assert->string($result[2][1])->is('w');
    }
}
