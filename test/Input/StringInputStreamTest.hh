<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\StringInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class StringInputStreamTest extends HackTest {
  public async function testReadFromStream(): Awaitable<void> {
    $input = new StringInputStream('abcd');

    expect($input->eof())->toBeFalse();

    $firstContent = await $input->readAsync(1);
    expect($input->eof())->toBeFalse();
    expect($firstContent)->toBeSame('a');

    $lastContent = await $input->readAsync(3);
    expect($input->eof())->toBeTrue();
    expect($lastContent)->toBeSame('bcd');
  }

  public function testOpenState(): void {
    $input = new StringInputStream('abcd');

    expect($input->isOpened())->toBeTrue();
    expect($input->isClosed())->toBeFalse();

    $input->close();

    expect($input->isOpened())->toBeFalse();
    expect($input->isClosed())->toBeTrue();
  }
}
