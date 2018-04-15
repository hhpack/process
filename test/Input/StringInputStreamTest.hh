<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\StringInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class StringInputStreamTest {
  <<Test>>
  public async function readFromStream(Assert $assert): Awaitable<void> {
    $input = new StringInputStream('abcd');

    $assert->bool($input->eof())->is(false);

    $firstContent = await $input->readAsync(1);
    $assert->bool($input->eof())->is(false);
    $assert->string($firstContent)->is('a');

    $lastContent = await $input->readAsync(3);
    $assert->bool($input->eof())->is(true);
    $assert->string($lastContent)->is('bcd');
  }

  <<Test>>
  public function openState(Assert $assert): void {
    $input = new StringInputStream('abcd');

    $assert->bool($input->isOpened())->is(true);
    $assert->bool($input->isClosed())->is(false);

    $input->close();

    $assert->bool($input->isOpened())->is(false);
    $assert->bool($input->isClosed())->is(true);
  }
}
