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

final class ProcessBuilder
{

    private DescriptorRegistry $descriptors;

    public function __construct(
        private string $command,
        private string $cwd = (string) getcwd(),
        private ?environment $env = null
    )
    {
        $this->descriptors = DescriptorRegistry::fromArray([
            new Descriptor(PipeType::Stdin, [ 'pipe', 'r' ]),
            new Descriptor(PipeType::Stdout, [ 'pipe', 'w' ]),
            new Descriptor(PipeType::Stderr, [ 'pipe', 'w' ])
        ]);
    }

    public function start() : ChildProcess
    {
        $pipeHandles = [];

        $process = proc_open(
            $this->command,
            $this->descriptors->toArray(),
            $pipeHandles,
            $this->cwd,
            $this->env
        );

        if (is_resource($process) === false) {
            throw new RuntimeException('Failed to start of process');
        }

        $pipeManager = $this->descriptors->createPipeManager($pipeHandles);

        return new ChildProcess($process, $pipeManager);
    }

}
