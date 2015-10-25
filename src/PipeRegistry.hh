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

final class PipeRegistry implements PipeManager
{

    public function __construct(
        private Vector<ReadablePipe> $readablePipes,
        private Vector<WritablePipe> $writablePipes
    )
    {
    }

    public function readablePipes() : Iterable<ReadablePipe>
    {
        return $this->readablePipes->items(); 
    }

    public function writablePipes() : Iterable<WritablePipe>
    {
        return $this->writablePipes->items();
    }

    public function read() : void
    {
        foreach ($this->readablePipes() as $pipe) {
            while ($pipe->eof() === false) {
                $pipe->read(4096);
            }
        }
    }

    public function close() : void
    {
        foreach ($this->pipes()->items() as $pipe) {
            if ($pipe->isClosed()) {
                continue;
            }
            $pipe->close();
        }
    }

    public function getOutputResult() : OutputResult
    {
        $outputs = [];

        foreach ($this->readablePipes() as $pipe) {
            if ($pipe->isStdout()) {
                $outputs['stdout'] = $pipe->getOutput();
            } else if ($pipe->isStderr()) {
                $outputs['stderr'] = $pipe->getOutput();
            }
        }

        return OutputResult::fromOutputs(shape(
            'stdout' => $outputs['stdout'],
            'stderr' => $outputs['stderr']
        ));
    }

    <<__Memoize>>
    private function pipes() : ImmVector<Stream>
    {
        $streams = Vector {};

        foreach ($this->writablePipes() as $stream) {
            $streams->add($stream);
        }
        foreach ($this->readablePipes() as $stream) {
            $streams->add($stream);
        }

        return $streams->toImmVector();
    }

    public function __destruct()
    {
        $this->close();
    }

}
