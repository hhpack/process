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

use hhpack\process\Writable;
use hhpack\process\output\OutputBufferedStream;

final class ProcessOptions
{

    private Writable<int> $output;
    private Writable<int> $errorOutput;

    public function __construct()
    {
        $this->output = new OutputBufferedStream();
        $this->errorOutput = new OutputBufferedStream();
    }

    public function stdout(Writable<int> $output) : this
    {
        $this->output = $output;
        return $this;
    }

    public function stderr(Writable<int> $output) : this
    {
        $this->errorOutput = $output;
        return $this;
    }

    public function applyTo(ProcessBuilder $bulider) : void
    {
        $bulider->stdout($this->output);
        $bulider->stderr($this->errorOutput);
    }

}
