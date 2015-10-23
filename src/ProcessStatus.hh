<?hh // strict

namespace hhpack\process;

final class ProcessStatus
{

    private string $command;
    private int $pid;
    private bool $running;
    private bool $signaled;
    private bool $stopped;
    private int $exitcode;
    private int $termsig;
    private int $stopsig;

    public function __construct(
        CapturedProcessStatus $status
    )
    {
        $this->command = $status['command'];
        $this->pid = $status['pid'];
        $this->running = $status['running'];
        $this->signaled = $status['signaled'];
        $this->stopped = $status['stopped'];
        $this->exitcode = $status['exitcode'];
        $this->termsig = $status['termsig'];
        $this->stopsig = $status['stopsig'];
    }

    public function isAlive() : bool
    {
        return $this->running;
    }

    public static function fromCapturedStatus(CapturedProcessStatus $status) : ProcessStatus
    {
        return new ProcessStatus($status);
    }

}
