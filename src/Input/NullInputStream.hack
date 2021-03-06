/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Input;

final class NullInputStream implements ReadableStream {

  private bool $opened = true;

  public function eof(): bool {
    return true;
  }

  public function isOpened(): bool {
    return $this->opened;
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  public async function readAsync(int $length = 4096): Awaitable<string> {
    return '';
  }

  public function close(): void {
    $this->opened = false;
  }

}
