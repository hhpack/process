<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process;
use hhpack\process\ProcessOptions;
use hhpack\process\output\Stdout;
use hhpack\process\output\Stderr;

async function pipe_example() : Awaitable<void>
{
    $cwd = (string) getcwd();

    $options = new ProcessOptions();
    $options->stdout(new Stdout());
    $options->stderr(new Stderr());

    $result = await process\exec('hh_client restart', $cwd, null, $options);
    $result->display();

    $result = await process\exec('hh_client check --json', $cwd, null, $options);
    $result->display();
}

pipe_example();
