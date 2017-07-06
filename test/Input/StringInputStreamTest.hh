<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\StringInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class StringInputStreamTest
{
    <<Test>>
    public function readFromStream(Assert $assert) : void
    {
        $input = new StringInputStream('abcd');

        $assert->bool($input->eof())->is(false);

        $firstContent = $input->read(1);
        $assert->bool($input->eof())->is(false);
        $assert->string($firstContent)->is('a');

        $lastContent = $input->read(3);
        $assert->bool($input->eof())->is(true);
        $assert->string($lastContent)->is('bcd');
    }

    <<Test>>
    public function openState(Assert $assert) : void
    {
        $input = new StringInputStream('abcd');

        $assert->bool($input->isOpened())->is(true);
        $assert->bool($input->isClosed())->is(false);

        $input->close();

        $assert->bool($input->isOpened())->is(false);
        $assert->bool($input->isClosed())->is(true);
    }
}
