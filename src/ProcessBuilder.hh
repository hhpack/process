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
use hhpack\process\output\OutputBufferedStream;
use RuntimeException;

final class ProcessBuilder
{

    private Writable<int> $output;
    private Writable<int> $errorOutput;
    private DescriptorRegistry $descriptors;

    public function __construct(
        private string $command,
        private string $cwd = (string) getcwd(),
        private ?environment $env = null
    )
    {
        $this->output = new OutputBufferedStream();
        $this->errorOutput = new OutputBufferedStream();

        $this->descriptors = new DefaultDescriptorRegistry(
            new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
            new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ]),
            new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ])
        );
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

    public function setOptions(ProcessOptions $options) : this
    {
        $options->applyTo($this);
        return $this;
    }

    public function start() : ChildProcess
    {
        $streamHandles = [];

        $descriptors = new DefaultDescriptorRegistry(
            new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ]),
            new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ], $this->output),
            new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ], $this->errorOutput)
        );

        $process = proc_open(
            $this->command,
            $this->descriptors->toArray(),
            $streamHandles,
            $this->cwd,
            $this->env
        );

        if (is_resource($process) === false) {
            throw new RuntimeException('Failed to start of process');
        }

        $streamManager = $descriptors->createPipeManager($streamHandles);

        return new ChildProcess($process, $streamManager);
    }

}
