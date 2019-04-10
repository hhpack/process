namespace HHPack\Process\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Process as process;
use HHPack\Process\ExecOptions;
use HHPack\Process\Input\FileInputStream;

<<__EntryPoint>>
async function exec_file_example(): Awaitable<noreturn> {
  $options = new ExecOptions();
  $options->stdin(new FileInputStream(__DIR__.'/data/input.txt'));

  $result = await process\execFile(
    __DIR__.'/scripts/exec_file_script.hh',
    [],
    $options,
  );
  echo (string)$result->stdout();

  exit(0);
}
