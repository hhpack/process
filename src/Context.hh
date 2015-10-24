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

interface Context
{
    public function start() : void;
    public function stop() : ProcessResult;
    public async function wait() : Awaitable<ProcessResult>;
    public function isAlive() : bool;
}
