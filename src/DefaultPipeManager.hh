<?hh // strict

namespace hhpack\process;

final class DefaultPipeManager implements PipeManager
{
    private WritablePipe $stdin;
    private ReadablePipe $stdout;
    private ReadablePipe $stderr;

    public function __construct(
        array<PipeType, resource> $pipeHandles
    )
    {
        $this->devNull();
        $this->applyHandles($pipeHandles);
    }

    private function devNull() : void
    {
        $this->stdin = WritablePipe::nullPipe();
        $this->stdout = ReadablePipe::nullPipe();
        $this->stderr = ReadablePipe::nullPipe();
    }

    public function read() : void
    {
        $pipes = [ $this->stdout, $this->stderr ];

        foreach ($pipes as $pipe) {
            while ($pipe->eof() === false) {
                $pipe->read(4096);
            }
        }
    }

    public function close() : void
    {
        $pipes = [ $this->stdin, $this->stdout, $this->stderr ];

        foreach ($pipes as $pipe) {
            $pipe->close();
        }
    }

    public function getResult() : Result
    {
        return Result::fromOutputs(shape(
            'stdout' => $this->stdout->getOutput(),
            'stderr' => $this->stderr->getOutput()
        ));
    }

    private function applyHandles(array<PipeType, resource> $pipeHandles) : void
    {
        foreach ($pipeHandles as $type => $pipeHandle) {
            if ($type === PipeType::Stdin) {
                $this->stdin = new WritablePipe($pipeHandle);
            } else if ($type === PipeType::Stdout) {
                $this->stdout = new ReadablePipe($pipeHandle);
            } else if ($type === PipeType::Stderr) {
                $this->stderr = new ReadablePipe($pipeHandle);
            }
        }
    }

    public static function fromResources(array<PipeType, resource> $pipeHandles) : DefaultPipeManager
    {
        return new DefaultPipeManager($pipeHandles);
    }

    public static function fromArray(array<int, resource> $pipeHandles) : DefaultPipeManager
    {
        $handles = [];

        foreach ($pipeHandles as $type => $pipeHandle) {
            $pipeType = PipeType::assert($type);
            $handles[$pipeType] = $pipeHandle;
        }

        return new DefaultPipeManager($handles);
    }

}
