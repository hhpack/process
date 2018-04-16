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

final class ResourceInputStream implements ReadableStream<int> {

  public function __construct(private resource $handle) {
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

  /**
   * Read asynchronously from stream
   */
  public async function readAsync(int $length = 4096): Awaitable<string> {
    $result =
      \HH\Asio\join(stream_await($this->handle, STREAM_AWAIT_READ, 0.2));

    if ($result === STREAM_AWAIT_READY) {
      return $this->readBytes($length);
    }

    if ($result === STREAM_AWAIT_ERROR) {
      throw new \RuntimeException("stream error");
    }

    // STREAM_AWAIT_TIMEOUT or STREAM_AWAIT_CLOSED
    return '';
  }

  private function readBytes(int $length = 4096): string {
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
