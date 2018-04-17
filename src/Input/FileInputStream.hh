<?hh // strict

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
use RuntimeException;

final class FileInputStream implements ReadableStream {

  private resource $handle;

  public function __construct(string $path) {
    $this->handle = fopen($path, 'r');

    if (!is_resource($this->handle)) {
      throw new RuntimeException(
        sprintf('Failed to open the file %s', $path),
      );
    }
    stream_set_blocking($this->handle, false);
  }

  public function eof(): bool {
    return feof($this->handle);
  }

  public function isOpened(): bool {
    return is_resource($this->handle);
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  public async function readAsync(int $length = 4096): Awaitable<string> {
    $bufferedOutput = '';

    while (($chunk = fread($this->handle, 16384)) !== false) {
      if ((string) $chunk === '') {
        break;
      }
      $bufferedOutput .= (string) $chunk;
    }

    if ($this->eof() && strlen($bufferedOutput) <= 0) {
      $this->close();
    }

    return $bufferedOutput;
  }

  public function close(): void {
    if ($this->isClosed()) {
      return;
    }
    fclose($this->handle);
  }

}
