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

use hhpack\process\StreamType;
use hhpack\process\descriptor\ReadDescriptor;
use hhpack\process\descriptor\WriteDescriptor;
use hhpack\process\descriptor\DescriptorRegistry;
use RuntimeException;

final class ProcessBuilder
{

    private DescriptorRegistry $descriptors;

    public function __construct(
        private string $command,
        private string $cwd = (string) getcwd(),
        private ?environment $env = null
    )
    {
        $this->descriptors = new DescriptorRegistry(
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

    public function environment(environment $environment) : this
    {
        $this->env = $environment;
        return $this;
    }

    public function start() : ChildProcess
    {
        $streamHandles = [];

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

        $streamManager = $this->descriptors->createPipeManager($streamHandles);

        return new ChildProcess($process, $streamManager);
    }

}
