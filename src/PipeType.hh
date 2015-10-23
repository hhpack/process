<?hh // strict

namespace hhpack\process;

enum PipeType : int
{
    Stdin = 0;
    Stdout = 1;
    Stderr = 2;
}
