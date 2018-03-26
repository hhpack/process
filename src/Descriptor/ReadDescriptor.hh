<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Descriptor;

use HHPack\Process\Writable;
use HHPack\Process\Stream\StreamType;
use HHPack\Process\Input\{ReadableStream, ProcessReadStream};
use HHPack\Process\Output\BufferedOutputStream;
use LogicException;

final class ReadDescriptor
  implements DescriptorSpecification<ProcessReadStream> {

  private StreamType $streamType;

  public function __construct(
    StreamType $streamType,
    private array<string> $streamValues,
    private Writable<int> $output = new BufferedOutputStream(),
  ) {
    $supportedType = ($streamType === StreamType::Stdout ||
                      $streamType === StreamType::Stderr);

    if (!$supportedType) {
      throw new LogicException('Type of stream must be stdout or stderr');
    }
    $this->streamType = $streamType;
  }

  // STDOUT, STDERR
  public function type(): StreamType {
    return $this->streamType;
  }

  // ['pipe', 'r'], ['pipe', 'w']
  public function values(): array<string> {
    return $this->streamValues;
  }

  public function createStreamFromHandle(resource $handle): ProcessReadStream {
    return new ProcessReadStream($this->streamType, $handle, $this->output);
  }

}
