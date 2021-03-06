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

final class Stderr implements WritableStream {

  public function isOpened(): bool {
    return \is_resource(\STDERR);
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  public function close(): void {}

  public async function writeAsync(string $output): Awaitable<int> {
    \fputs(\STDERR, $output);
    return \strlen($output);
  }

}
