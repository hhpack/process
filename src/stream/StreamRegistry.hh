<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\stream;

use hhpack\process\Stream;
use hhpack\process\OutputResult;
use hhpack\process\input\ProcessReadStream;
use hhpack\process\output\ProcessWriteStream;

final class StreamRegistry implements StreamManager
{

    public function __construct(
        private Vector<ProcessReadStream> $readableStreams,
        private Vector<ProcessWriteStream> $writableStreams
    )
    {
    }

    public function readableStreams() : Iterable<ProcessReadStream>
    {
        return $this->readableStreams->items(); 
    }

    public function writableStreams() : Iterable<ProcessWriteStream>
    {
        return $this->writableStreams->items();
    }

    public async function read() : Awaitable<void>
    {
        foreach ($this->readableStreams() as $stream) {
            $stream->read();
        }
    }

    public async function write() : Awaitable<void>
    {
        foreach ($this->writableStreams() as $stream) {
            $stream->flush();
        }
    }

    public function close() : void
    {
        foreach ($this->streams()->items() as $stream) {
            if ($stream->isClosed()) {
                continue;
            }
            $stream->close();
        }
    }

    public function getOutputResult() : OutputResult
    {
        $outputs = [];

        foreach ($this->readableStreams() as $stream) {
            if ($stream->isStdout()) {
                $outputs['stdout'] = $stream->getOutput();
            } else if ($stream->isStderr()) {
                $outputs['stderr'] = $stream->getOutput();
            }
        }

        return OutputResult::fromOutputs(shape(
            'stdout' => $outputs['stdout'],
            'stderr' => $outputs['stderr']
        ));
    }

    <<__Memoize>>
    private function streams() : ImmVector<Stream>
    {
        $streams = Vector {};

        foreach ($this->writableStreams() as $stream) {
            $streams->add($stream);
        }
        foreach ($this->readableStreams() as $stream) {
            $streams->add($stream);
        }

        return $streams->toImmVector();
    }

    public function __destruct()
    {
        $this->close();
    }

}
