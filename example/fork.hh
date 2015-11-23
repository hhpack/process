<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process;
use hhpack\process\ProcessOptions;
use hhpack\process\output\Stdout;
use hhpack\process\output\Stderr;

async function fork_example() : Awaitable<void>
{
    $process = process\fork(__DIR__ . '/fork_script.hh', [ 'a', 'b' ]);

    $result = await $process->wait();
    $result->display();
}

fork_example();
