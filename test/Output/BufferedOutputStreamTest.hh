<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Output\BufferedOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class BufferedOutputStreamTest
{
    <<Test>>
    public function writeToBuffer(Assert $assert) : void
    {
        $output = new BufferedOutputStream();
        $output->write('text');

        $assert->string((string) $output)->is('text');
    }
}
