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

use hhpack\process\PipeType;
use hhpack\process\StreamManager;
use hhpack\process\stream\StreamRegistry;
use hhpack\process\DescriptorSpecification;
use hhpack\process\input\ReadablePipe;
use hhpack\process\output\WritablePipe;


final class DescriptorRegistry
{

    public function __construct(
        private ImmMap<PipeType, DescriptorSpecification> $registry
    )
    {
    }

    public function createPipeManager(array<int, resource> $pipeHandles) : StreamManager
    {
        $readablePipes = Vector {};
        $writablePipes = Vector {};

        foreach ($pipeHandles as $type => $pipeHandle) {
            $pipeType = PipeType::assert($type);

            if ($pipeType === PipeType::Stdin) {
                $writablePipes->add(new WritablePipe($pipeType, $pipeHandle));
            } else if ($pipeType === PipeType::Stdout) {
                $readablePipes->add(new ReadablePipe($pipeType, $pipeHandle));
            } else if ($pipeType === PipeType::Stderr) {
                $readablePipes->add(new ReadablePipe($pipeType, $pipeHandle));
            }
        }

        return new StreamRegistry($readablePipes, $writablePipes);
    }

    public function toArray() : array<int, array<string>>
    {
        $result = $this->registry->mapWithKey(($type, $descriptor) ==> {
            return $descriptor->getPipeValues();
        });
        return $result->toArray();
    }

    public static function fromArray(Traversable<DescriptorSpecification> $descriptors) : DescriptorRegistry
    {
        $registry = Map {};

        foreach ($descriptors as $descriptor) {
            $registry->set($descriptor->getPipeType(), $descriptor);
        }

        return new DescriptorRegistry( $registry->toImmMap() );
    }

}
