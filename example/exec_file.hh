<?hh // partial

namespace HHPack\Process\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Process;
use HHPack\Process\ExecOptions;
use HHPack\Process\Input\FileInputStream;

async function exec_file_example() : Awaitable<void>
{
  $options = new ExecOptions();
  $options->stdin(new FileInputStream(__DIR__ . '/data/input.txt'));

  $result = await process\execFile(__DIR__ . '/scripts/exec_file_script.hh', [], $options);
  echo (string) $result->stdout();
}

exec_file_example();
