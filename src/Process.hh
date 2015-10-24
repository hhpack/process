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

    public async function run() : Awaitable<ProcessResult>
    {
        return await $this->context->run();
    }

    public function start() : void
    {
        $this->context->start();
    }

    public function stop() : ProcessResult
    {
        return $this->context->stop();
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
