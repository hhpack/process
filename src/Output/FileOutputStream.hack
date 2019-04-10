/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Output;

use RuntimeException;

final class FileOutputStream implements WritableStream {

  private ResourceOutputStream $stream;

  public function __construct(string $path) {
    $handle = \fopen($path, 'w');

    if (!\is_resource($handle)) {
      throw new RuntimeException(\sprintf('Failed to open the file %s', $path));
    }

    $this->stream = new ResourceOutputStream($handle);
  }

  public function isOpened(): bool {
    return $this->stream->isOpened();
  }

  public function isClosed(): bool {
    return $this->stream->isClosed();
  }

  public async function writeAsync(string $output): Awaitable<int> {
    return await $this->stream->writeAsync($output);
  }

  public function close(): void {
    $this->stream->close();
  }

}
