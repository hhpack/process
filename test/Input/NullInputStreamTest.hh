<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\NullInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class NullInputStreamTest extends HackTest {
  public async function testReadFromStream(): Awaitable<void> {
    $input = new NullInputStream();
    $readContents = await $input->readAsync();

    expect($readContents)->toBeSame('');
  }

  public function testOpenState(): void {
    $input = new NullInputStream();

    expect($input->isOpened())->toBeTrue();
    expect($input->isClosed())->toBeFalse();

    $input->close();

    expect($input->isOpened())->toBeFalse();
    expect($input->isClosed())->toBeTrue();
  }
}
