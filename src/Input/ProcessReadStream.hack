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
use HHPack\Process\Output\BufferedOutputStream;
use HHPack\Process\Stream\StreamType;

final class ProcessReadStream implements ReadableStream {

  private ResourceInputStream $stream;

  public function __construct(
    private StreamType $type,
    resource $handle,
    private Writable<int> $output = new BufferedOutputStream(),
  ) {
    $this->stream = new ResourceInputStream($handle);
  }

  public function eof(): bool {
    return $this->stream->eof();
  }

  public function isOpened(): bool {
    return $this->stream->isOpened();
  }

  public function isClosed(): bool {
    return $this->stream->isClosed();
  }

  public async function readAsync(int $length = 4096): Awaitable<string> {
    $chunk = await $this->stream->readAsync($length);

    if ($chunk === '') {
      return '';
    }

    await $this->output->writeAsync($chunk);

    return $chunk;
  }

  public function getOutput(): Output {
    return $this->output;
  }

  public function isStdout(): bool {
    return $this->type === StreamType::Stdout;
  }

  public function isStderr(): bool {
    return $this->type === StreamType::Stderr;
  }

  public function close(): void {
    $this->stream->close();
  }

}
