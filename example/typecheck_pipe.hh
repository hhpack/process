<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process;
use hhpack\process\ProcessOptions;
use hhpack\process\output\Stdout;
use hhpack\process\output\Stderr;

async function pipe_example() : Awaitable<void>
{
    $options = new ProcessOptions();
    $options->stdout(new Stdout());
    $options->stderr(new Stderr());

    await process\exec('hh_client restart', $options);
    await process\exec('hh_client check --json', $options);
}

pipe_example();
