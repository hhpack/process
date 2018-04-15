<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Output\NullOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class NullOutputStreamTest {
  <<Test>>
  public async function writeToBuffer(Assert $assert): Awaitable<void> {
    $output = new NullOutputStream();
    $bytes = await $output->writeAsync('text');

    $assert->int($bytes)->eq(4);
  }

  <<Test>>
  public function openState(Assert $assert): void {
    $output = new NullOutputStream();
    $assert->bool($output->isOpened())->is(true);
    $assert->bool($output->isClosed())->is(false);

    $output->close();

    $assert->bool($output->isOpened())->is(false);
    $assert->bool($output->isClosed())->is(true);
  }
}
