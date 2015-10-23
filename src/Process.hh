<?hh // strict

namespace hhpack\process;

use RuntimeException;

final class Process
{

    private ?resource $process;
    private array<int, array<string>> $descriptors = [
        0 => [ 'pipe', 'r' ],
        1 => [ 'pipe', 'w' ],
        2 => [ 'pipe', 'w' ]
    ];
    private PipeManager $pipeManager;
    private ProcessStatus $status;

    public function __construct(
        private string $command
    )
    {
        $this->pipeManager = new NullPipeManager();
        $this->status = ProcessStatus::initialStatus();
    }

    public function execute() : int
    {
        $this->start();
        return $this->wait();
    }

    private function start() : void
    {
        $pipeHandles = [];

        $this->process = proc_open(
            $this->command,
            $this->descriptors,
            $pipeHandles
        );

        $this->pipeManager = DefaultPipeManager::fromArray($pipeHandles);
        $this->captureStatus();
    }

    private function stop() : int
    {
        $this->pipeManager->close();
        proc_close($this->process);
        return $this->getExitCode();
    }

    private function wait() : int
    {
        do {
            $this->captureStatus();
            $this->pipeManager->read();
            $this->captureStatus();
        } while($this->isAlive());

        return $this->stop();
    }

    public function isAlive() : bool
    {
        return $this->status->isAlive();
    }

    private function getExitCode() : int
    {
        return $this->status->getExitCode();
    }

    private function captureStatus() : void
    {
        if ($this->process === null) {
            throw new RuntimeException();
        }
        $this->status = ProcessStatus::fromResource($this->process);
    }

}
