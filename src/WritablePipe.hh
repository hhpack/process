<?hh // strict

namespace hhpack\process;

use RuntimeException;

final class WritablePipe implements WritableStream
{

    private bool $opened = true;

    public function __construct(
        private resource $handle
    )
    {
    }

    public function opened() : bool
    {
        return $this->opened;
    }

    public function write(string $output) : int
    {
        return (int) fwrite($this->handle, $output);
    }

    public function close() : void
    {
        fclose($this->handle);
        $this->opened = false;
    }

    public static function nullPipe() : WritablePipe
    {
        $handle = fopen('/dev/null', 'w');

        if (is_resource($handle) === false) {
            throw new RuntimeException();
        }
        return new WritablePipe($handle);
    }

}
