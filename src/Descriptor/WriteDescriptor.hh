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

use HHPack\Process\Input\{ NullInputStream, ReadableStream };
use HHPack\Process\Output\{ WritableStream, ProcessWriteStream };
use HHPack\Process\Stream\StreamType;
use LogicException;

final class WriteDescriptor implements DescriptorSpecification<ProcessWriteStream>
{

    private StreamType $streamType;

    public function __construct(
        StreamType $streamType,
        private array<string> $streamValues,
        private ReadableStream<int> $input = new NullInputStream()
    )
    {
        if ($streamType !== StreamType::Stdin) {
            throw new LogicException('Type of stream must be stdin');
        }
        $this->streamType = $streamType;
    }

    // STDIN
    public function type() : StreamType
    {
        return $this->streamType;
    }

    // ['pipe', 'r'], ['pipe', 'w']
    public function values() : array<string>
    {
        return $this->streamValues;
    }

    public function createStreamFromHandle(resource $handle) : ProcessWriteStream
    {
        return new ProcessWriteStream($this->streamType, $handle, $this->input);
    }

}
