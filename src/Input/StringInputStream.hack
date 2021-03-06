/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Input;

use HHPack\Process\Writable;

final class StringInputStream implements ReadableStream {

  private bool $opened = true;

  public function __construct(private string $input) {}

  public function eof(): bool {
    return \strlen($this->input) <= 0;
  }

  public function isOpened(): bool {
    return $this->opened;
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  public async function readAsync(int $length = 4096): Awaitable<string> {
    $content = \substr($this->input, 0, $length);
    $this->input = \substr($this->input, $length);
    return $content;
  }

  public function close(): void {
    $this->opened = false;
  }

}
