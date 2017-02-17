<?hh // partial

namespace HHPack\Process\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Process;

async function main() : Awaitable<void>
{
    $result = await Process\exec('hh_client restart');
    $result->display();

    $result = await Process\exec('hh_client check --json');
    $result->display();
}

main();
