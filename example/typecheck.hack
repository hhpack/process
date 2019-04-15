namespace HHPack\Process\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Process;

<<__EntryPoint>>
async function main(): Awaitable<noreturn> {
  $result = await Process\exec('hh_client restart');
  $result->display();

  $result = await Process\exec('hh_client check --json');
  $result->display();

  exit(0);
}
