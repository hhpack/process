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

use hhpack\process\output\OutputBufferedStream;

final class OutputResult implements Displayable
{

    public function __construct(
        private OutputBufferedStream $stdout,
        private OutputBufferedStream $stderr
    )
    {
    }

    public function getStdout() : OutputBufferedStream
    {
        return $this->stdout;
    }

    public function getStderr() : OutputBufferedStream
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
            new OutputBufferedStream(),
            new OutputBufferedStream()
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
