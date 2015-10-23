<?hh // strict

namespace hhpack\process;

final class Process
{

    private ?resource $process;
    private array<int, array<string>> $descriptors = [
        0 => [ 'pipe', 'r' ],
        1 => [ 'pipe', 'w' ],
        2 => [ 'pipe', 'w' ]
    ];
    private ?PipeManager $pipeManager = null;

    public function __construct(
        private string $command
    )
    {
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

        $this->pipeManager = PipeManager::fromArray($pipeHandles);
    }

    private function stop() : int
    {
        if ($this->pipeManager === null) {
            return -1;
        }
        $this->pipeManager->closeAll();
        return proc_close($this->process);
    }

    private function wait() : int
    {
        if ($this->pipeManager === null) {
            return -1;
        }
        $this->pipeManager->readAll();
        return $this->stop();
    }

    public function isRunning() : bool
    {
        return $this->pipeManager !== null;
    }

}
