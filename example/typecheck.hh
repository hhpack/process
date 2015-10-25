<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process\Process;
use hhpack\process\GeneralContext;

async function main() : Awaitable<void>
{
    $result = await Process::exec('hh_client restart');
    $result->display();

    $result = await Process::exec('hh_client check --json');
    $result->display();
}

main();
