<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\descriptor;

use hhpack\process\input\NullInputStream;
use hhpack\process\input\ReadableStream;
use hhpack\process\output\WritableStream;
use hhpack\process\output\ProcessWriteStream;
use hhpack\process\stream\StreamType;

final class WriteDescriptor implements DescriptorSpecification<ProcessWriteStream>
{

    public function __construct(
        private StreamType $streamType,
        private array<string> $streamValues,
        private ReadableStream<int> $input = new NullInputStream()
    )
    {
    }

    // STDIN, STDOUT, STDERR
    public function getStreamType() : StreamType
    {
        return $this->streamType;
    }

    public function isReadDescriptor() : bool
    {
        return false;
    }

    public function isWriteDescriptor() : bool
    {
        return true;
    }

    // ['pipe', 'r'], ['pipe', 'w']
    public function getStreamValues() : array<string>
    {
        return $this->streamValues;
    }

    public function createStreamFromHandle(resource $handle) : ProcessWriteStream
    {
        return new ProcessWriteStream($this->streamType, $handle, $this->input);
    }

}
