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


final class GeneralContext extends ProcessContext implements Context
{

    private array<int, array<string>> $descriptors = [
        0 => [ 'pipe', 'r' ],
        1 => [ 'pipe', 'w' ],
        2 => [ 'pipe', 'w' ]
    ];

    public function __construct(
        private string $command
    )
    {
        $this->pipeManager = new NullPipeManager();
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

        $this->process = proc_open(
            $this->command,
            $this->descriptors,
            $pipeHandles
        );

        $this->pipeManager = DefaultPipeManager::fromArray($pipeHandles);
        $this->captureStatus();
    }

}
