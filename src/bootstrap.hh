<?hh // strict

namespace hhpack\process
{
    type Outputs = shape(
        'stdout' => BufferedOutput,
        'stderr' => BufferedOutput
    );
}
