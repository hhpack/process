<?hh // strict

namespace hhpack\process
{
    type Outputs = shape(
        'stdout' => BufferedOutput,
        'stderr' => BufferedOutput
    );

    type CapturedProcessStatus = shape(
        'command' => string,
        'pid' => int,
        'running' => bool,
        'signaled' => bool,
        'stopped' => bool,
        'exitcode' => int,
        'termsig' => int,
        'stopsig' => int
    );
}
