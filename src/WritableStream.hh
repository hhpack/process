<?hh // strict

namespace hhpack\process;

interface WritableStream extends Stream
{
    public function write(string $output) : int;
}
