<?hh // strict

namespace hhpack\process;

interface Stream
{
    public function opened() : bool;
    public function close() : void;
}
