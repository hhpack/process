<?hh // strict

namespace hhpack\process;

final class BufferedOutput
{

    public function __construct(
        private string $output = ''
    )
    {
    }

    public function append(string $chunk) : void
    {
        $this->output .= $chunk;
    }

    public function __toString() : string
    {
        return $this->output;
    }

}
