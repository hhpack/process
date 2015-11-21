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

final class ProcessResult implements Displayable
{

    public function __construct(
        private ProcessStatus $status,
        private OutputResult $output
    )
    {
    }

    public function getExitCode() : int
    {
        return $this->status->getExitCode();
    }

    public function getStdout() : OutputBufferedStream
    {
        return $this->output->getStdout();
    }

    public function getStderr() : OutputBufferedStream
    {
        return $this->output->getStderr();
    }

    public function display() : void
    {
        fwrite(STDOUT, (string) $this);
    }

    public function __toString() : string
    {
        return sprintf(
            "EXIT_CODE: %s\n\n%s\n",
            (string) $this->status->getExitCode(),
            (string) $this->output
        );
    }

}
