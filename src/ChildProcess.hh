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

final class ChildProcess
{

    private ProcessStatus $status;

    public function __construct(
        private resource $process,
        private PipeManager $pipeManager
    )
    {
        $this->captureStatus();
    }

    public function pid() : ?int
    {
        return $this->status->getPid();
    }

    public async function stop() : Awaitable<ProcessResult>
    {
        $this->captureStatus();

        if ($this->isAlive() === false) {
            return $this->close();
        }

        proc_terminate($this->process);

        while($this->isAlive()) {
            usleep(1000);
            $this->captureStatus();
        }

        return $this->close();
    }

    public async function wait() : Awaitable<ProcessResult>
    {
        do {
            $this->captureStatus();
            $this->pipeManager->read();
            $this->captureStatus();
        } while($this->isAlive());

        return $this->close();
    }

    public function isAlive() : bool
    {
        return $this->status->isAlive();
    }

    protected function close() : ProcessResult
    {
        $this->pipeManager->close();
        proc_close($this->process);

        return new ProcessResult(
            $this->status,
            $this->pipeManager->getOutputResult()
        );
    }

    private function captureStatus() : void
    {
        $this->status = ProcessStatus::fromResource($this->process);
    }

    protected function __destruct()
    {
        $this->close();
    }

}