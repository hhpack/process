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

use RuntimeException;

final class GeneralContext extends ProcessContext implements Context
{

    private DescriptorRegistry $descriptors;

    public function __construct(
        string $command,
        string $cwd = (string) getcwd(),
        ?environment $env = null
    )
    {
        $this->command = $command;
        $this->workingDirectory = $cwd;
        $this->enviromentVariables = new ImmMap($env);
        $this->pipeManager = new NullPipeManager();
        $this->descriptors = DescriptorRegistry::fromArray([
            new Descriptor(PipeType::Stdin, [ 'pipe', 'r' ]),
            new Descriptor(PipeType::Stdout, [ 'pipe', 'w' ]),
            new Descriptor(PipeType::Stderr, [ 'pipe', 'w' ])
        ]);
        $this->status = ProcessStatus::initialStatus();
    }

    public async function run() : Awaitable<ProcessResult>
    {
        $this->start();
        return await $this->wait();
    }

    public function start() : void
    {
        $pipeHandles = [];

        $environment = $this->getEnvironmentVariables();
        $environment = $environment->isEmpty() ? null : $environment->toArray();

        $this->process = proc_open(
            $this->command,
            $this->descriptors->toArray(),
            $pipeHandles,
            $this->getWorkingDirectory(),
            $environment
        );

        if (is_resource($this->process) === false) {
            throw new RuntimeException('Failed to start of process');
        }

        $this->pipeManager = $this->descriptors->createPipeManager($pipeHandles);
        $this->captureStatus();
    }

}