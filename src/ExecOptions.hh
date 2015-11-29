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

final class ExecOptions implements Options
{

    public function __construct(
        private string $cwd = (string) getcwd(),
        private ?environment $env = null
    )
    {
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

    public function applyTo(ProcessBuilder $bulider) : void
    {
        $bulider->environment($this->env);
        $bulider->workingDirectory($this->cwd);
    }

}
