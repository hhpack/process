<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Output\NullOutputStream;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class NullOutputStreamTest extends HackTest {
  public async function testWriteToBuffer(): Awaitable<void> {
    $output = new NullOutputStream();
    $bytes = await $output->writeAsync('text');

    expect($bytes)->toBeSame(4);
  }

  public function testOpenState(): void {
    $output = new NullOutputStream();

    expect($output->isOpened())->toBeTrue();
    expect($output->isClosed())->toBeFalse();

    $output->close();

    expect($output->isOpened())->toBeFalse();
    expect($output->isClosed())->toBeTrue();
  }
}
