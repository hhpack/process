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

use HHPack\Process\Stream\{StreamType, StreamManager, StreamRegistry};
use HHPack\Process\Input\ProcessReadStream;
use HHPack\Process\Output\ProcessWriteStream;

final class DefaultDescriptorRegistry implements DescriptorRegistry {

  public function __construct(
    private DescriptorSpecification<ProcessWriteStream> $stdin,
    private DescriptorSpecification<ProcessReadStream> $stdout,
    private DescriptorSpecification<ProcessReadStream> $stderr,
  ) {}

  public function createStreamManager(
    array<int, resource> $streamHandles,
  ): StreamManager {
    $readableStreams = Vector {};
    $writableStreams = Vector {};

    foreach ($streamHandles as $type => $streamHandle) {
      $streamType = StreamType::assert($type);

      if ($streamType === StreamType::Stdin) {
        $writableStreams->add(
          $this->stdin->createStreamFromHandle($streamHandle),
        );
      } else if ($streamType === StreamType::Stdout) {
        $readableStreams->add(
          $this->stdout->createStreamFromHandle($streamHandle),
        );
      } else if ($streamType === StreamType::Stderr) {
        $readableStreams->add(
          $this->stderr->createStreamFromHandle($streamHandle),
        );
      }
    }

    return new StreamRegistry($readableStreams, $writableStreams);
  }

  public function toArray(): array<array<string>> {
    return [
      $this->stdin->values(),
      $this->stdout->values(),
      $this->stderr->values(),
    ];
  }

}
