<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Output\BufferedOutputStream;
use HackPack\HackUnit\Contract\Assert;

final class BufferedOutputStreamTest {
  <<Test>>
  public async function writeToBuffer(Assert $assert): Awaitable<void> {
    $output = new BufferedOutputStream();
    await $output->writeAsync('text');

    $assert->string((string) $output)->is('text');
  }
}
