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
use hhpack\process\output\BufferedOutputStream;

final class ProcessOptions
{

    private Writable<int> $output;
    private Writable<int> $errorOutput;

    public function __construct(
        private string $cwd = (string) getcwd(),
        private ?environment $env = null
    )
    {
        $this->cwd = (string) getcwd();
        $this->output = new BufferedOutputStream();
        $this->errorOutput = new BufferedOutputStream();
    }

    public function workingDirectory(string $cwd) : this
    {
        $this->cwd = $cwd;
        return $this;
    }

    public function environment(?environment $environment = null) : this
    {
        $this->env = $environment;
        return $this;
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
        $bulider->environment($this->env);
        $bulider->workingDirectory($this->cwd);
        $bulider->stdout($this->output);
        $bulider->stderr($this->errorOutput);
    }

}
