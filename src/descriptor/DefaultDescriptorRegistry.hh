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
use hhpack\process\input\ProcessReadStream;
use hhpack\process\output\ProcessWriteStream;

final class DefaultDescriptorRegistry implements DescriptorRegistry
{

    public function __construct(
        private DescriptorSpecification<ProcessWriteStream> $stdin,
        private DescriptorSpecification<ProcessReadStream> $stdout,
        private DescriptorSpecification<ProcessReadStream> $stderr
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
                $writableStreams->add( $this->stdin->createStreamFromHandle($streamHandle) );
            } else if ($streamType === StreamType::Stdout) {
                $readableStreams->add( $this->stdout->createStreamFromHandle($streamHandle) );
            } else if ($streamType === StreamType::Stderr) {
                $readableStreams->add( $this->stderr->createStreamFromHandle($streamHandle) );
            }
        }

        return new StreamRegistry($readableStreams, $writableStreams);
    }

    public function toArray() : array<int, array<string>>
    {
        return [
            $this->stdin->getStreamValues(),
            $this->stdout->getStreamValues(),
            $this->stderr->getStreamValues()
        ];
    }

}
