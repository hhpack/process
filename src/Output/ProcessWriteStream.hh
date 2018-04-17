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

use HHPack\Process\Input\{NullInputStream, StringInputStream, ReadableStream};
use HHPack\Process\Output\BufferedOutputStream;
use HHPack\Process\Stream\StreamType;

final class ProcessWriteStream implements WritableStream {

  private ResourceOutputStream $stream;
  private string $bufferedInput = '';

  public function __construct(
    private StreamType $type,
    resource $handle,
    private ReadableStream $input = new NullInputStream(),
  ) {
    $this->stream = new ResourceOutputStream($handle);
  }

  public function isOpened(): bool {
    return $this->stream->isOpened();
  }

  public function isClosed(): bool {
    return $this->stream->isClosed();
  }

  public async function flush(): Awaitable<void> {
    await $this->readAll();
    await $this->writeAll();
  }

  public async function writeAsync(string $output): Awaitable<int> {
    return await $this->stream->writeAsync($output);
  }

  public function close(): void {
    $this->stream->close();
  }

  private async function readAll(): Awaitable<void> {
    if ($this->input->isClosed()) {
      return;
    }

    $chunk = await $this->input->readAsync();

    if ($this->input->eof()) {
      $this->input->close();
    }

    $this->bufferedInput .= $chunk;
  }

  // XXX append ready?
  private async function writeAll(): Awaitable<void> {
    if ($this->isClosed()) {
      return;
    }

    while (strlen($this->bufferedInput) > 0) {
      $chunk = substr($this->bufferedInput, 0, 512);
      $writedBytes = await $this->writeAsync($chunk);

      if ($writedBytes <= 0) {
        break;
      }
      $this->bufferedInput = substr($this->bufferedInput, $writedBytes);
    }

    if (strlen($this->bufferedInput) > 0 || $this->input->isOpened()) {
      return;
    }

    $this->close();
  }

}
