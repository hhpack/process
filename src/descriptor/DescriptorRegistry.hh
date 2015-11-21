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
use hhpack\process\StreamManager;
use hhpack\process\stream\StreamRegistry;
use hhpack\process\DescriptorSpecification;
use hhpack\process\input\ReadablePipe;
use hhpack\process\output\WritablePipe;


final class DescriptorRegistry
{

    public function __construct(
        private ImmMap<StreamType, DescriptorSpecification> $registry
    )
    {
    }

    public function createPipeManager(array<int, resource> $streamHandles) : StreamManager
    {
        $readableStreams = Vector {};
        $writableStreams = Vector {};

        foreach ($streamHandles as $type => $streamHandle) {
            $streamType = StreamType::assert($type);

            if ($streamType === StreamType::Stdin) {
                $writableStreams->add(new WritablePipe($streamType, $streamHandle));
            } else if ($streamType === StreamType::Stdout) {
                $readableStreams->add(new ReadablePipe($streamType, $streamHandle));
            } else if ($streamType === StreamType::Stderr) {
                $readableStreams->add(new ReadablePipe($streamType, $streamHandle));
            }
        }

        return new StreamRegistry($readableStreams, $writableStreams);
    }

    public function toArray() : array<int, array<string>>
    {
        $result = $this->registry->mapWithKey(($type, $descriptor) ==> {
            return $descriptor->getStreamValues();
        });
        return $result->toArray();
    }

    public static function fromArray(Traversable<DescriptorSpecification> $descriptors) : DescriptorRegistry
    {
        $registry = Map {};

        foreach ($descriptors as $descriptor) {
            $registry->set($descriptor->getStreamType(), $descriptor);
        }

        return new DescriptorRegistry( $registry->toImmMap() );
    }

}
