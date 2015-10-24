<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process\Process;
use hhpack\process\GeneralContext;

async function main() : Awaitable<void>
{
    $process = new Process(new GeneralContext('hh_client restart'));

    $result = await $process->run();
    $result->display();

    $process = new Process(new GeneralContext('hh_client check'));

    $result = await $process->run();
    $result->display();
}

main();
