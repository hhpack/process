<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process;

async function main() : Awaitable<void>
{
    $result = await process\exec('hh_client restart');
    $result->display();

    $result = await process\exec('hh_client check --json');
    $result->display();
}

main();
