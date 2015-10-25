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


final class DescriptorRegistry
{

    public function __construct(
        private ImmMap<PipeType, DescriptorSpecification> $registry
    )
    {
    }

    public function createPipeManager(array<int, resource> $pipeHandles) : PipeManager
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

        return new PipeRegistry($readablePipes, $writablePipes);
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
