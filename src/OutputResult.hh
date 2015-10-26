<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

final class OutputResult implements Displayable
{

    public function __construct(
        private BufferedOutput $stdout,
        private BufferedOutput $stderr
    )
    {
    }

    public function getStdout() : BufferedOutput
    {
        return $this->stdout;
    }

    public function getStderr() : BufferedOutput
    {
        return $this->stderr;
    }

    public static function fromOutputs(Outputs $outputs) : OutputResult
    {
        return new OutputResult(
            $outputs['stdout'],
            $outputs['stderr']
        );
    }

    public static function emptyResult() : OutputResult
    {
        return new OutputResult(
            new BufferedOutput(),
            new BufferedOutput()
        );
    }

    public function display() : void
    {
        fwrite(STDOUT, (string) $this);
    }

    public function __toString() : string
    {
        return sprintf(
            "STDOUT: \n%s\n\nSTDERR: \n%s",
            (string) $this->stdout,
            (string) $this->stderr
        );
    }

}
