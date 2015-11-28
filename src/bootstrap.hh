<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process
{
    use hhpack\process\output\OutputBufferedStream;

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

namespace hhpack\process\input
{
    use hhpack\process\Writable;

    type Output = Writable<int>;
}
