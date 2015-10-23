<?hh // strict

namespace hhpack\process;

interface ReadableStream extends Stream
{
    public function eof() : bool;
    public function read(int $length) : void;
    public function getOutput() : BufferedOutput;
}
