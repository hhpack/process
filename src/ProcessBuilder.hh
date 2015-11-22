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
use hhpack\process\stream\StreamType;
use hhpack\process\descriptor\ReadDescriptor;
use hhpack\process\descriptor\WriteDescriptor;
use hhpack\process\descriptor\DescriptorRegistry;
use hhpack\process\descriptor\DefaultDescriptorRegistry;
use hhpack\process\descriptor\DescriptorSpecification;
use hhpack\process\output\BufferedOutputStream;
use RuntimeException;

final class ProcessBuilder
{

    private string $cwd;
    private Mode $mode;
    private ?environment $env;
    private Writable<int> $output;
    private Writable<int> $errorOutput;

    public function __construct(
        private string $command,
        ProcessOptions $options = new ProcessOptions()
    )
    {
        $this->cwd = (string) getcwd();
        $this->mode = Mode::Normal;
        $this->env = null;
        $this->output = new BufferedOutputStream();
        $this->errorOutput = new BufferedOutputStream();
        $options->applyTo($this);
    }

    public function mode(Mode $mode) : this
    {
        $this->mode = $mode;
        return $this;
    }

    public function command(string $command) : this
    {
        $this->command = $command;
        return $this;
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

    public function start() : ChildProcess
    {
        $streamHandles = [];
        $descriptors = $this->createDescriptors();

        $process = proc_open(
            $this->command,
            $descriptors->toArray(),
            $streamHandles,
            $this->cwd,
            $this->env
        );

        if (is_resource($process) === false) {
            throw new RuntimeException('Failed to start of process');
        }

        $streamManager = $descriptors->createStreamManager($streamHandles);

        return new ChildProcess($process, $streamManager);
    }

    private function createDescriptors() : DescriptorRegistry
    {
        return new DefaultDescriptorRegistry(
            new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
            new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ], $this->output),
            new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ], $this->errorOutput)
        );
    }

}
