<?hh // partial

namespace hhpack\process\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\process;
use hhpack\process\ExecOptions;
use hhpack\process\input\FileInputStream;

async function exec_file_example() : Awaitable<void>
{
    $options = new ExecOptions();
    $options->stdin(new FileInputStream(__DIR__ . '/input.txt'));

    $result = await process\execFile(__DIR__ . '/exec_file_script.hh', [], $options);
    echo (string) $result->stdout();
}

exec_file_example();
