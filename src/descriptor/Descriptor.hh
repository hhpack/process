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

final class Descriptor implements DescriptorSpecification
{

    private DescriptorType $descriptorType;

    public function __construct(
        private StreamType $pipeType,
        private array<string> $pipeValues
    )
    {
        $this->resolveDescriptorType($pipeValues);
    }

    // STDIN, STDOUT, STDERR
    public function getPipeType() : StreamType
    {
        return $this->pipeType;
    }

    public function isReadDescriptor() : bool
    {
        return $this->descriptorType === DescriptorType::Read;
    }

    public function isWriteDescriptor() : bool
    {
        return $this->descriptorType === DescriptorType::Write;
    }

    // ['pipe', 'r'], ['pipe', 'w']
    public function getPipeValues() : array<string>
    {
        return $this->pipeValues;
    }

    private function resolveDescriptorType(array<string> $pipeValues) : void
    {
        $descriptorType = DescriptorType::Read;
        $lastIndex = count($pipeValues) - 1;

        if ($pipeValues[$lastIndex] === 'r') {
            $descriptorType = DescriptorType::Write;
        }

        $this->descriptorType = $descriptorType;
    }

}
