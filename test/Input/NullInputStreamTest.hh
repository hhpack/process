<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\NullInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class NullInputStreamTest
{
    <<Test>>
    public function readFromStream(Assert $assert) : void
    {
        $input = new NullInputStream();
        $assert->string((string) $input->read())->is('');
    }

    <<Test>>
    public function openState(Assert $assert) : void
    {
        $input = new NullInputStream();

        $assert->bool($input->isOpened())->is(true);
        $assert->bool($input->isClosed())->is(false);

        $input->close();

        $assert->bool($input->isOpened())->is(false);
        $assert->bool($input->isClosed())->is(true);
    }
}
