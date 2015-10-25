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

final class Process
{

    public function __construct(
        private Context $context
    )
    {
    }

    public function getPid() : ?int
    {
        return $this->context->getPid();
    }

    public function getCommand() : string
    {
        return $this->context->getCommand();
    }

    public function getWorkingDirectory() : string
    {
        return $this->context->getWorkingDirectory();
    }

    public function getEnvironmentVariables() : EnviromentVariables
    {
        return $this->context->getEnvironmentVariables();
    }

    public async function run() : Awaitable<ProcessResult>
    {
        return await $this->context->run();
    }

    public function start() : void
    {
        $this->context->start();
    }

    public async function stop() : Awaitable<ProcessResult>
    {
        return await $this->context->stop();
    }

    public async function wait() : Awaitable<ProcessResult>
    {
        return await $this->context->wait();
    }

    public function isAlive() : bool
    {
        return $this->context->isAlive();
    }

}
