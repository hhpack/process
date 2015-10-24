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

abstract class ProcessContext implements Context
{

    protected string $command;
    protected string $workingDirectory;
    protected EnviromentVariables $enviromentVariables;
    protected ?resource $process;
    protected PipeManager $pipeManager;
    protected ProcessStatus $status;

    public function getPid() : int
    {
        return $this->status->getPid();
    }

    public function getCommand() : string
    {
        return $this->command;
    }

    public function getWorkingDirectory() : string
    {
        return $this->workingDirectory;
    }

    public function getEnvironmentVariables() : EnviromentVariables
    {
        return $this->enviromentVariables;
    }

    // FIXME SIGTERM, SIGKILL
    public function stop() : ProcessResult
    {
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

    protected function captureStatus() : void
    {
        if ($this->process === null) {
            throw new RuntimeException();
        }
        $this->status = ProcessStatus::fromResource($this->process);
    }

}
