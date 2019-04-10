namespace HHPack\Process\Test;

use HHPack\Process\Input\FileInputStream;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class FileInputStreamTest extends HackTest {
  public async function testReadFromStream(): Awaitable<void> {
    $path = __DIR__.'/../fixtures/input.txt';
    $input = new FileInputStream($path);

    $readContents = await $input->readAsync();

    expect($readContents)->toBeSame("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
  }

  public function testOpenState(): void {
    $path = __DIR__.'/../fixtures/input.txt';
    $input = new FileInputStream($path);

    expect($input->isOpened())->toBeTrue();
    expect($input->isClosed())->toBeFalse();

    $input->close();

    expect($input->isOpened())->toBeFalse();
    expect($input->isClosed())->toBeTrue();
  }
}
