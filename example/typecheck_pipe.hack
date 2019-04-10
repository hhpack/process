namespace HHPack\Process\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Process;
use HHPack\Process\ProcessOptions;
use HHPack\Process\Output\{Stdout, Stderr};

<<__EntryPoint>>
async function pipe_example(): Awaitable<noreturn> {
  $options = new ProcessOptions();
  $options->stdout(new Stdout());
  $options->stderr(new Stderr());

  using ($p = Process\spawn('hh_client restart', [], $options)) {
    await $p->wait();
  }

  using ($p = Process\spawn('hh_client check --json', [], $options)) {
    await $p->wait();
  }

  exit(0);
}
