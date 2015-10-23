<?hh // strict

namespace hhpack\process;

final class Pipe
{

    private BufferedOutput $bufferedOutput;

    public function __construct(
        private resource $handle
    )
    {
        $this->bufferedOutput = new BufferedOutput();
    }

    public function eof() : bool
    {
        return feof($this->handle);
    }

    public function read(int $length) : void
    {
        $chunk = fread($this->handle, $length);
        $this->bufferedOutput->append($chunk);
    }

    public function getOutput() : BufferedOutput
    {
        return $this->bufferedOutput;
    }

    public function close() : void
    {
        fclose($this->handle);
    }

}
