<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

use RuntimeException;

final class FileDescriptor implements DescriptorSpecification
{

    public function __construct(
        private PipeType $pipeType,
        private DescriptorType $descriptorType, 
        private array<string> $pipeValues
    )
    {
    }

    // STDIN, STDOUT, STDERR
    public function getPipeType() : PipeType
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

}
