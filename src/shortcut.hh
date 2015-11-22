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

use hhpack\process\output\OutputBufferedStream;

async function exec(
    string $command,
    ProcessOptions $options = new ProcessOptions()
) : Awaitable<ProcessResult>
{
    $builder = new ProcessBuilder($command, $options);
    return await $builder->start()->wait();
}
