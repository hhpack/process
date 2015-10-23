<?hh // strict

namespace hhpack\process;

interface PipeManager
{
    public function read() : void;
    public function close() : void;
    public function getResult() : Result;
}
