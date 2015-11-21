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

use hhpack\process\Writable;
use hhpack\process\StreamType;
use hhpack\process\DescriptorType;
use hhpack\process\DescriptorSpecification;
use hhpack\process\output\OutputBufferedStream;
use hhpack\process\input\ReadableStream;
use hhpack\process\input\InputPipeStream;

final class ReadDescriptor implements DescriptorSpecification<InputPipeStream>
{

    public function __construct(
        private StreamType $streamType,
        private array<string> $streamValues,
        private Writable<int> $output = new OutputBufferedStream()
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
        return true;
    }

    public function isWriteDescriptor() : bool
    {
        return false;
    }

    // ['pipe', 'r'], ['pipe', 'w']
    public function getStreamValues() : array<string>
    {
        return $this->streamValues;
    }

    public function createStreamFromHandle(resource $handle) : InputPipeStream
    {
        return new InputPipeStream($this->streamType, $handle, $this->output);
    }

}
