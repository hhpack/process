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
    type EnviromentVariables = ImmMap<string, string>;

    type Outputs = shape(
        'stdout' => BufferedOutput,
        'stderr' => BufferedOutput
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
