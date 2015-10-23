<?hh // strict

namespace hhpack\process;

final class NullPipeManager implements PipeManager
{

    public function read() : void
    {
    }

    public function close() : void
    {
    }

    public function getResult() : Result
    {
        return Result::emptyResult();
    }

}
