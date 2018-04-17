<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Input\FileInputStream;
use HackPack\HackUnit\Contract\Assert;

final class FileInputStreamTest {
  <<Test>>
  public async function readFromStream(Assert $assert): Awaitable<void> {
    $path = __DIR__.'/../fixtures/input.txt';
    $input = new FileInputStream($path);

    $readContents = await $input->readAsync();

    $assert->string($readContents)->is("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
  }

  <<Test>>
  public function openState(Assert $assert): void {
    $path = __DIR__.'/../fixtures/input.txt';
    $input = new FileInputStream($path);

    $assert->bool($input->isOpened())->is(true);
    $assert->bool($input->isClosed())->is(false);

    $input->close();

    $assert->bool($input->isOpened())->is(false);
    $assert->bool($input->isClosed())->is(true);
  }
}
