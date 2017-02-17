<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process;

use RuntimeException;

async function exec(
    string $command,
    ExecOptions $options = new ExecOptions()
) : Awaitable<ProcessResult>
{
    $builder = new ProcessBuilder($command, $options);
    return await $builder->start()->wait();
}

async function execFile(
    string $file,
    ?Traversable<mixed> $args = [],
    ExecOptions $options = new ExecOptions()
) : Awaitable<ProcessResult>
{
    if (is_file($file) === false) {
        throw new RuntimeException(sprintf('%s is not a file', $file));
    }

    $arguments = ImmSet::fromItems($args)->map(($value) ==> {
        return trim((string) $value);
    })->toArray();

    $command = sprintf('hhvm %s %s', trim($file), implode(' ', $arguments));

    return await exec($command, $options);
}

function fork(
    string $script,
    ?Traversable<mixed> $args = [],
    ProcessOptions $options = new ProcessOptions()
) : ChildProcess
{
    $arguments = ImmSet::fromItems($args)->map(($value) ==> {
        return trim((string) $value);
    })->toArray();

    $command = sprintf('hhvm %s %s', trim($script), implode(' ', $arguments));
    $builder = new ProcessBuilder($command, $options);

    return $builder->start();
}

function spawn(
    string $command,
    ?Traversable<mixed> $args = [],
    ProcessOptions $options = new ProcessOptions()
) : ChildProcess
{
    $arguments = ImmSet::fromItems($args)->map(($value) ==> {
        return trim((string) $value);
    })->toArray();

    $command = sprintf('%s %s', trim($command), implode(' ', $arguments));
    $builder = new ProcessBuilder($command, $options);

    return $builder->start();
}
