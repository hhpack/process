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

async function exec(string $command, string $cwd = (string) getcwd(), ?environment $env = null) : Awaitable<ProcessResult>
{
    $builder = new ProcessBuilder($command, $cwd, $env);
    return await $builder->start()->wait();
}
