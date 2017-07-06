<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\WriteDescriptor;
use LogicException;
use HackPack\HackUnit\Contract\Assert;

final class WriteDescriptorTest
{
    <<Test>>
    public function unsupportType(Assert $assert) : void
    {
        $assert->whenCalled(() ==> {
            $descriptor = new WriteDescriptor(StreamType::Stdout, [ 'pipe', 'r' ]);
        })->willThrowClass(LogicException::class);
    }
}
