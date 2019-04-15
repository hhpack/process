namespace HHPack\Process\Test;

use HHPack\Process\Output\BufferedOutputStream;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class BufferedOutputStreamTest extends HackTest {
  public async function testWriteToBuffer(): Awaitable<void> {
    $output = new BufferedOutputStream();
    await $output->writeAsync('text');

    expect((string)$output)->toBeSame('text');
  }
}
