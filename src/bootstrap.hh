<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process
{
    use HHPack\Process\Output\OutputBufferedStream;

    type environment = KeyedTraversable<string, string>;
    type EnviromentVariables = ImmMap<string, string>;

    type Output = Writable<int>;

    type Outputs = shape(
        'stdout' => Output,
        'stderr' => Output
    );

    type CapturedProcessStatus = shape(
        'command' => string,
        'pid' => ?int,
        'running' => bool,
        'signaled' => bool,
        'stopped' => bool,
        'exitcode' => int,
        'termsig' => int,
        'stopsig' => int
    );
}

namespace HHPack\Process\Input
{
    use HHPack\Process\Writable;

    type Output = Writable<int>;
}
