/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Output;

use HHPack\Process\Writable;

final class NullOutputStream implements WritableStream {

  private bool $opened = true;

  public function isOpened(): bool {
    return $this->opened;
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  public function close(): void {
    $this->opened = false;
  }

  public async function writeAsync(string $output): Awaitable<int> {
    return \strlen($output);
  }
}
