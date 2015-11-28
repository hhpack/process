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

use hhpack\process\stream\StreamManager;
use RuntimeException;

final class ChildProcess
{

    private ProcessStatus $status;

    public function __construct(
        private resource $process,
        private StreamManager $streamManager
    )
    {
        $this->status = ProcessStatus::initial();
        $this->captureStatus();
    }

    public function pid() : ?int
    {
        return $this->status->pid();
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
            $this->streamManager->write();
            $this->streamManager->read();
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
        $this->streamManager->close();
        proc_close($this->process);

        return new ProcessResult(
            $this->status,
            $this->streamManager->getOutputResult()
        );
    }

    private function captureStatus() : void
    {
        if ($this->status->isAlive() === false) {
            return;
        }
        $this->status = ProcessStatus::fromResource($this->process);
    }

    protected function __destruct()
    {
        $this->close();
    }

}
