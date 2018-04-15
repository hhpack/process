<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Output;

final class ResourceOutputStream implements WritableStream {

  public function __construct(private resource $handle) {
    stream_set_blocking($this->handle, false);
  }

  public function isOpened(): bool {
    return is_resource($this->handle);
  }

  public function isClosed(): bool {
    return $this->isOpened() === false;
  }

  /**
   * Write asynchronously from stream
   */
  public async function writeAsync(string $output): Awaitable<int> {
    $result = await stream_await($this->handle, STREAM_AWAIT_WRITE, 0.2);

    if ($result === STREAM_AWAIT_READY) {
      return $this->write($output);
    }

    if ($result === STREAM_AWAIT_ERROR) {
      throw new \RuntimeException("stream error");
    }

    // STREAM_AWAIT_TIMEOUT or STREAM_AWAIT_CLOSED
    return 0;
  }

  public function ready(): bool {
    $read = [];
    $write = [$this->handle];
    $expect = null;

    if ($this->isClosed()) {
      return false;
    }

    $ng =
      ($num = stream_select(&$read, &$write, &$expect, 0, 200000)) === false;

    if ($ng || $num <= 0) {
      return false;
    }

    return true;
  }

  public function notReady(): bool {
    return $this->ready() === false;
  }

  public function write(string $output): int {
    return (int) fwrite($this->handle, $output);
  }

  public function close(): void {
    if ($this->isClosed()) {
      return;
    }
    fclose($this->handle);
  }
}
