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

use hhpack\process\StreamType;
use hhpack\process\DescriptorType;
use hhpack\process\DescriptorSpecification;

final class ReadDescriptor implements DescriptorSpecification
{

    public function __construct(
        private StreamType $streamType,
        private array<string> $streamValues
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

}
