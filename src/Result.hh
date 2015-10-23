<?hh // strict

namespace hhpack\process;

final class Result
{

    public function __construct(
        private BufferedOutput $stdout,
        private BufferedOutput $stderr
    )
    {
    }

    public static function fromOutputs(Outputs $outputs) : Result
    {
        return new Result(
            $outputs['stdout'],
            $outputs['stderr']
        );
    }

}
