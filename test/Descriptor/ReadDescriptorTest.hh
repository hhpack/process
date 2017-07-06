<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\ReadDescriptor;
use LogicException;
use HackPack\HackUnit\Contract\Assert;

final class ReadDescriptorTest
{
    <<Test>>
    public function unsupportType(Assert $assert) : void
    {
        $assert->whenCalled(() ==> {
            $descriptor = new ReadDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]);
        })->willThrowClass(LogicException::class);
    }
}
